#pragma once

#include "family.hpp"

namespace mak
{
	struct pancake_sort;
}

struct mak::pancake_sort : mak::base_sorting_algorithm<
	mak::pancake_sort,
	mak::pancake_sort_family,
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

		for (; first != last; ++first)
		{
			auto extreme = ranges::min_element(first, last, is_before_2_way);
			if (extreme != first)
			{
				ranges::reverse(extreme, last);
				ranges::reverse(first, last);

				// can improve, but lose the characteristic of pancake:
				// ranges::reverse(first, extreme + 1);
			}
		}
	}
};
