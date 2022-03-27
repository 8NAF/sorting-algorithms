#pragma once

#include "family.hpp"

namespace mak
{
	struct bingo_sort;
}

struct mak::bingo_sort : mak::base_sorting_algorithm<
	mak::bingo_sort,
	mak::selection_sort_family,
	std::forward_iterator_tag
>
{
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> forward_iterator_t,
		iter_comparator<forward_iterator_t> comparator_t = default_comparator
	> static void sort
	(
		forward_iterator_t first,
		forward_iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto is_before_2_way = transform_to_2_way<forward_iterator_t>(is_before);

		while (first != last)
		{
			auto extreme = ranges::min_element(first, last, is_before_2_way);
			ranges::iter_swap(extreme, first);
			extreme = first;
			++first;

			ranges::for_each(first, last,
				[&first, &extreme](auto&& value) {
					if (value == *extreme)
					{
						ranges::swap(*first, value);
						++first;
					}
				}
			);
		}
	}
};
