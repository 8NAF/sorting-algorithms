#pragma once

#include "family.hpp"

namespace mak
{
	struct iterative_quick_sort;
}

struct mak::iterative_quick_sort : mak::base_sorting_algorithm<
	mak::iterative_quick_sort,
	mak::quick_sort_family,
	std::bidirectional_iterator_tag
>
{
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> bidirectional_iterator_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
	static constexpr void
	sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		std::stack<
			std::pair<bidirectional_iterator_t, bidirectional_iterator_t>
		> order;
		order.emplace(first, last);

		while (not order.empty())
		{
			auto [left, right] = order.top();
			order.pop();

			auto pivot = family.partition(left, right);

			if (not no_need_to_sort(left, pivot)) {
				order.emplace(left, pivot);
			}
			if (not no_need_to_sort(pivot, right)) {
				order.emplace(pivot, right);
			}
		}
	}
};
