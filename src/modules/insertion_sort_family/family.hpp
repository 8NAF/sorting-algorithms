#pragma once

#include "family.abstract.hpp"
#include "types/integer.type.hpp"

#include <list>
#include <forward_list>

namespace mak
{
	using mak::types::make_unsigned_t;

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
		auto stored_value = ranges::iter_move(last);
		for (auto current = last; current != first; ) {
			auto temp = ranges::prev(current, gap);
			*current = ranges::iter_move(temp);
			current = temp;
		}
		*first = std::move(stored_value);
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
	std::invocable<
		search_function_t,
		bidirectional_iterator_t,
		bidirectional_iterator_t,
		decltype(insertion_sort_family::is_before),
		make_unsigned_t<bidirectional_iterator_t>
	>
	{
		auto sub_last = ranges::next(first, gap);
		auto sub_first = first;
		auto d_first_sub_last = gap;

		while (sub_last != last)
		{
			auto inserted_position = search(sub_first, sub_last, this->is_before, gap);
			rotate_right(inserted_position, sub_last, gap);

			++sub_last;
			++d_first_sub_last;
			sub_first = (d_first_sub_last % gap == 0) ? first : ranges::next(sub_first);
		}
	}

	static constexpr auto
	binary_search
	(
		forward_iterator_t first,
		forward_iterator_t last,
		decltype(insertion_sort_family::is_before) is_before,
		make_unsigned_t<forward_iterator_t> gap
	)
	{
		if (gap == 1) {
			return ranges::upper_bound(first, last, *last, is_before);
		}

		// TODO: handle case - gap > 1
		return first;
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
		auto current = ranges::prev(last, gap);
		while (current != first and is_before(*last, *current)) {
			current = ranges::prev(current, gap);
		}
		return is_before(*last, *current) ? current : ranges::next(current, gap);
	}
};
