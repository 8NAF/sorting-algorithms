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

		auto middle = midpoint(first, o_last);
		for (auto last = o_last; first != middle; ++first)
		{
			auto [left, right] = ranges::minmax_element(first, last, family.is_before);

			bool are_all_sorted = family.is_equal(*left, *right);
			if (are_all_sorted) break;

			--last;
			right = (first != right) ? right : left;

			ranges::iter_swap(first, left);
			ranges::iter_swap(last, right);
		}

		return o_last;
	}
};
