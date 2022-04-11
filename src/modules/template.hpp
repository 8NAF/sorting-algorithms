#pragma once

#include "family.hpp"

namespace mak
{
	struct _sort;
}

struct mak::_sort : mak::base_sorting_algorithm<
	mak::_sort,
	mak::_sort_family,
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
	static constexpr void
		sort
		(
			bidirectional_iterator_t first,
			sentinel_t last,
			comparator_t is_before = {},
			projection_t projection = {}
		)
	{
		auto o_last = get_last_iterator(first, sentinel);
		if (no_need_to_sort(first, o_last)) return o_last;

		auto family = family_t<
			bidirectional_iterator_t,
			comparator_t,
			projection_t
		>(std::move(is_before), std::move(projection));
	}
};
