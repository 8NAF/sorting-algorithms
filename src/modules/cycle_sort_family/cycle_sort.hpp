#pragma once

#include "family.hpp"

namespace mak
{
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	struct cycle_sort;
};

struct mak::cycle_sort : mak::base_sorting_algorithm<
	mak::cycle_sort_family
>
{
	template <
		cycle_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto is_before_2_way = transform_to_2_way<iterator_t>(is_before);

		for (--last; last != first; --last)
		{
			auto const& last_value = *last;
			while (true)
			{
				auto n_before_last = ranges::count_if(
					first,
					last,
					[&](auto const& current_value) {
						return is_before_2_way(last_value, current_value);
					}
				);
				if (0 == n_before_last) break;

				auto expected_position = ranges::prev(last, n_before_last);
				for (; *expected_position == last_value; --expected_position);
				ranges::iter_swap(expected_position, last);
			}
		}
	}

	template <
		cycle_sort_family_cp::range range_t,
		iter_comparator<range_t> comparator_t = default_comparator
	> static void sort
	(
		range_t& range,
		comparator_t is_before = {}
	)
	{
		sort(ranges::begin(range), ranges::end(range), is_before);
	}

	template <
		class pointer_t,
		iter_comparator<pointer_t> comparator_t = default_comparator
	> static void sort
	(
		pointer_t pointer,
		std::size_t n,
		comparator_t is_before = {}
	) requires std::is_pointer_v<pointer_t>
	{
		sort(pointer, pointer + n, is_before);
	}
};

namespace mak
{
#undef iterator_t
#undef range_t
}
