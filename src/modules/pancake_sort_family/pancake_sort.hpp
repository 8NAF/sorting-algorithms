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
		std::sentinel_for<bidirectional_iterator_t> sentinel_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
	static constexpr auto
	sort
	(
		bidirectional_iterator_t first,
		sentinel_t last,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		if (no_need_to_sort(first, last)) {
			return get_last_iterator(first, last);
		}

		auto family = family_t<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		for (; first != last; ++first)
		{
			auto extreme = ranges::min_element(first, last, family.is_before);
			if (extreme != first)
			{
				ranges::reverse(extreme, last);
				ranges::reverse(first, last);

				// can improve, but lose the characteristic of pancake:
				// ranges::reverse(first, extreme + 1);
			}
		}

		return first;
	}
};
