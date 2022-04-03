#pragma once

#include "family.hpp"

namespace mak
{
	struct selection_sort;
}

struct mak::selection_sort : mak::base_sorting_algorithm<
	mak::selection_sort,
	mak::selection_sort_family,
	std::forward_iterator_tag
>
{
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> forward_iterator_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<forward_iterator_t, comparator_t, projection_t>
	static constexpr void
	sort
	(
		forward_iterator_t first,
		forward_iterator_t last,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		if (no_need_to_sort(first, last)) return;
		
		auto family = family_t<
			forward_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		while (first != last)
		{
			auto extreme = ranges::min_element(first, last, family.is_before);
			ranges::iter_swap(extreme, first);
			++first;
		}
	}
};
