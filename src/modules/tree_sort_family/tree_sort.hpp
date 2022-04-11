#pragma once

#include "family.hpp"

namespace mak
{
	struct tree_sort;
	using BST_sort = tree_sort;
}

struct mak::tree_sort : mak::base_sorting_algorithm<
	mak::tree_sort,
	mak::tree_sort_family,
	std::bidirectional_iterator_tag
>
{
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
			return ranges::next(first, last);
		}

		auto family = family_t<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		using value_t = std::iter_value_t<bidirectional_iterator_t>;
		BST <value_t, decltype(family.is_before)> tree(family.is_before);

		ranges::for_each(first, last,
			[&tree](auto& value) {
				tree.emplace(std::move(value));
			}
		);

		tree.LNR(
			[&first](auto const& value) mutable {
				*first = value;
				++first;
			}
		);

		return first;
	}
};
