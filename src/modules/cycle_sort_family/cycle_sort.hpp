#pragma once

#include "family.hpp"

namespace mak
{
	struct cycle_sort;
}

struct mak::cycle_sort : mak::base_sorting_algorithm<
	mak::cycle_sort,
	mak::cycle_sort_family,
	std::bidirectional_iterator_tag
>
{
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> bidirectional_iterator_t,
		iter_comparator<bidirectional_iterator_t> comparator_t = default_comparator
	> static void sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto is_before_2_way = transform_to_2_way<bidirectional_iterator_t>(is_before);

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
};
