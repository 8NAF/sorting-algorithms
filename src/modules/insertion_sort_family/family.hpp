#pragma once

#include "concepts/comparator.concept.hpp"
#include "types/integer.type.hpp"

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <forward_list>

namespace mak
{
#define	iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	using mak::functions::transform_to_2_way;
	using mak::types::make_unsigned_t;

	// for including header file
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;

	namespace insertion_sort_family_cp
	{
		template <class iterator_t>
		concept iterator = std::bidirectional_iterator<iterator_t>;
		template <class range_t>
		concept range = ranges::bidirectional_range<range_t>;
	}

	template<
		insertion_sort_family_cp::iterator iterator_t,
		concepts::iter_comparator<iterator_t> comparator_t
	> class insertion_sort_family;
}

template<
	mak::insertion_sort_family_cp::iterator iterator_t,
	mak::concepts::iter_comparator<iterator_t> comparator_t
>
class mak::insertion_sort_family {

private:

	static inline auto transform_to_2_way =
		transform_to_2_way<iterator_t, comparator_t>;

	std::invoke_result_t<decltype(transform_to_2_way), comparator_t> is_before;

	void rotate_right
	(
		iterator_t first,
		iterator_t last,
		make_unsigned_t<iterator_t> gap
	) const
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

	insertion_sort_family(comparator_t const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	template <
		std::invocable<
		iterator_t, iterator_t, decltype(is_before), make_unsigned_t<iterator_t>
		> Search_Function
	> void generic_insertion_sort
	(
		iterator_t first,
		iterator_t last,
		make_unsigned_t<iterator_t> gap,
		Search_Function search
	) const
	{
		auto sub_last = ranges::next(first, gap);
		auto sub_first = first;
		auto d_first_sub_last = ranges::distance(first, sub_last);

		while (sub_last != last)
		{
			auto inserted_position = search(sub_first, sub_last, is_before, gap);
			rotate_right(inserted_position, sub_last, gap);

			++sub_last;
			++d_first_sub_last;
			sub_first = (d_first_sub_last % gap == 0) ? first : ranges::next(sub_first);
		}
	}

	// requires Forward Iterator
	static auto binary_search
	(
		iterator_t first,
		iterator_t last,
		decltype(is_before) is_before,
		make_unsigned_t<iterator_t> gap
	)
	{
		if (gap == 1) {
			return ranges::upper_bound(first, last, *last, is_before);
		}

		// TODO: handle case - gap > 1
		return first;
	}

	static auto reverse_linear_search
	(
		iterator_t first,
		iterator_t last,
		decltype(is_before) is_before,
		make_unsigned_t<iterator_t> gap
	)
	{
		auto current = ranges::prev(last, gap);
		while (current != first and is_before(*last, *current)) {
			current = ranges::prev(current, gap);
		}
		return is_before(*last, *current) ? current : ranges::next(current, gap);
	}
};

namespace mak
{
#undef iterator_t
#undef range_t
}
