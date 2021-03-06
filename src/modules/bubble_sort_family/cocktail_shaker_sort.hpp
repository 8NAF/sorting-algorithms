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
		std::sentinel_for<bidirectional_iterator_t> sentinel_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
	static constexpr auto
	sort
	(
		bidirectional_iterator_t first,
		sentinel_t sentinel,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		auto o_last = get_last_iterator(first, sentinel);
		if (no_need_to_sort(first, o_last)) return o_last;

		auto family = family_t<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		for (auto last = ranges::prev(o_last); first != last; )
		{
			auto last_swap = family.find_last_swap(first, last);
			if (bool not_swapped = (last_swap == first); not_swapped) break;
			last = last_swap;

			last_swap = family.reverse_find_last_swap(first, last);
			if (bool not_swapped = (last_swap == last); not_swapped) break;
			first = last_swap;
		}

		return o_last;
	}
};
