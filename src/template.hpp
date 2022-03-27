#pragma once

#include "family.hpp"

namespace mak
{
	struct _sort;
}

struct mak::_sort : mak::base_sorting_algorithm<
	mak::_sort,
	mak::_sort_family,
	std::_tag
>
{
	template <
		tag_to_iterator<tag_t> iterator_t,
		iter_comparator<iterator_t> Comparator = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		Comparator is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<iterator_t, Comparator>(is_before);
	}
};

