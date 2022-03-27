#pragma once

#include "family.hpp"

namespace mak
{
	struct double_selection_sort;
	using double_ended_selection_sort = double_selection_sort;
}

struct mak::double_selection_sort : mak::base_sorting_algorithm<
	mak::double_selection_sort,
	mak::selection_sort_family,
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

		auto is_before_2_way = transform_to_2_way<
			bidirectional_iterator_t
		>(is_before);

		auto middle = midpoint(first, last);
		for (; first != middle; ++first)
		{
			auto [left, right] = ranges::minmax_element(first, last, is_before_2_way);
			if (bool are_all_sorted = (*left == *right); are_all_sorted) return;

			--last;
			right = (first != right) ? right : left;

			ranges::iter_swap(first, left);
			ranges::iter_swap(last, right);
		}
	}
};
