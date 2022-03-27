#pragma once

#include "family.hpp"

namespace mak
{
	struct binary_insertion_sort;
}

struct mak::binary_insertion_sort : mak::base_sorting_algorithm<
	mak::binary_insertion_sort,
	mak::insertion_sort_family,
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
		family.generic_insertion_sort(
			first,
			last,
			1,
			decltype(family)::binary_search
		);
	}
};
