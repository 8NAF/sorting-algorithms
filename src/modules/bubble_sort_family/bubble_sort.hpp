#pragma once

#include "family.hpp"

namespace mak
{
	struct bubble_sort;
	using sinking_sort = bubble_sort;
}

struct mak::bubble_sort : mak::base_sorting_algorithm<
	mak::bubble_sort,
	mak::bubble_sort_family,
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

		auto family = family_t<forward_iterator_t, comparator_t>(is_before);
		for (last = prev(first, last); first != last; )
		{
			auto last_swap = family.find_last_swap(first, last);
			if (bool not_swapped = (last_swap == first); not_swapped) return;
			last = last_swap;
		}
	}
};
