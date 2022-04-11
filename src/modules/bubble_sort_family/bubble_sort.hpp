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
		std::sentinel_for<forward_iterator_t> sentinel_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<forward_iterator_t, comparator_t, projection_t>
	static constexpr auto
	sort
	(
		forward_iterator_t first,
		sentinel_t sentinel,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		auto o_last = get_last_iterator(first, sentinel);
		if (no_need_to_sort(first, o_last)) return o_last;

		auto family = family_t<
			forward_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		for (auto last = prev(first, o_last); first != last; )
		{
			auto last_swap = family.find_last_swap(first, last);
			if (bool not_swapped = (last_swap == first); not_swapped) break;
			last = last_swap;
		}

		return o_last;
	}
};
