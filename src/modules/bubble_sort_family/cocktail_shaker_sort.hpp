#pragma once

#include "family.hpp"

namespace mak
{
	struct cocktail_shaker_sort;

	using cocktail_sort = cocktail_shaker_sort;
	using shaker_sort = cocktail_shaker_sort;
	using bidirectional_bubble_sort = cocktail_shaker_sort;
	using ripple_sort = cocktail_shaker_sort;
	using shuffle_sort = cocktail_shaker_sort;
	using shuttle_sort = cocktail_shaker_sort;
}

struct mak::cocktail_shaker_sort : mak::base_sorting_algorithm<
	mak::cocktail_shaker_sort,
	mak::bubble_sort_family,
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

		auto family = family_t<bidirectional_iterator_t, comparator_t>(is_before);
		for (--last; first != last; )
		{
			auto last_swap = family.find_last_swap(first, last);
			if (bool not_swapped = (last_swap == first); not_swapped) return;
			last = last_swap;

			last_swap = family.reverse_find_last_swap(first, last);
			if (bool not_swapped = (last_swap == last); not_swapped) return;
			first = last_swap;
		}
	}
};
