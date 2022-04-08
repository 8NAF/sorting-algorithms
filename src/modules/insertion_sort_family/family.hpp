#pragma once

#include "family.abstract.hpp"
#include "adaptors/jumping_iterator.adaptor.hpp"
#include "adaptors/cyclic_iterator.adaptor.hpp"
#include "types/integer.type.hpp"

#include <list>
#include <forward_list>

namespace mak
{
	using adaptors::jumping_iterator;
	using adaptors::cyclic_iterator;

	using types::make_unsigned_t;

	template<class iterator_t, class comparator_t, class projection_t>
	class insertion_sort_family;
}

template<class iterator_t, class comparator_t, class projection_t>
class mak::insertion_sort_family
	: private mak::base_family<iterator_t, comparator_t, projection_t>
{
private:
	using forward_iterator_t = iterator_t;
	using bidirectional_iterator_t = iterator_t;

	constexpr void
	rotate_right
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		make_unsigned_t<bidirectional_iterator_t> gap
	) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		auto rj_first = std::reverse_iterator(
			jumping_iterator(last, gap)
		);
		auto rj_last = std::reverse_iterator(
			jumping_iterator(first, gap)
		);

		if (rj_first != rj_last) {
			ranges::rotate(rj_first, ranges::next(rj_first), rj_last);
		}
	}

public:
	using base_family = base_family<iterator_t, comparator_t, projection_t>;
	using base_family::base_family;

	template <class search_function_t>
	constexpr void
	generic_insertion_sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		make_unsigned_t<bidirectional_iterator_t> gap,
		search_function_t search
	) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>&&
		std::invocable
		<
			search_function_t,
			bidirectional_iterator_t,
			bidirectional_iterator_t,
			decltype(insertion_sort_family::is_before),
			make_unsigned_t<bidirectional_iterator_t>
		>
	{
		auto head = cyclic_iterator(first, ranges::next(first, gap - 1));
		auto tail = cyclic_iterator(ranges::next(first, gap), last);

		while (tail.is_not_last())
		{
			auto inserted_position = std::invoke(
				search,
				head, tail, this->is_before, gap
			);
			rotate_right(inserted_position, ranges::next(tail, gap), gap);

			++tail;
			++head;
		}
	}

	static constexpr auto
	binary_search
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		decltype(insertion_sort_family::is_before) is_before,
		make_unsigned_t<forward_iterator_t> gap
	)
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		auto j_first = jumping_iterator(first, gap);
		auto j_last = jumping_iterator(last, gap);

		return ranges::upper_bound(j_first, j_last, *last, is_before);
	}

	static constexpr auto
	reverse_linear_search
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		decltype(insertion_sort_family::is_before) is_before,
		make_unsigned_t<bidirectional_iterator_t> gap
	)
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		auto rj_first = std::reverse_iterator(
			jumping_iterator(last, gap)
		);
		auto rj_last = std::reverse_iterator(
			jumping_iterator(first, gap)
		);

		auto rj_result = ranges::find_if(rj_first, rj_last, [&](auto&& value) {
			return !is_before(*last, value);
		});

		return rj_result.base();
	}
};
