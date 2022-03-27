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
		iter_comparator<bidirectional_iterator_t> comparator_t = default_comparator
	> static void sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<bidirectional_iterator_t>;
		using two_way_comparator_t = generic_comparator<value_t>;

		auto is_before_2_way = transform_to_2_way<bidirectional_iterator_t>(is_before);
		BST <value_t, two_way_comparator_t> tree(is_before_2_way);

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
	}
};
