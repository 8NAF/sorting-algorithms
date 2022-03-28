#pragma once

#include "family.hpp"

namespace mak
{
	struct quick_sort;
	using recursive_quick_sort = quick_sort;
}

class mak::quick_sort : public mak::base_sorting_algorithm<
	mak::quick_sort,
	mak::quick_sort_family,
	std::bidirectional_iterator_tag
>
{
private:
	template <
		tag_to_iterator<tag_t> bidirectional_iterator_t,
		iter_comparator<bidirectional_iterator_t> comparator_t
	> static void recursive_sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		family_t<bidirectional_iterator_t, comparator_t> const& family
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto pivot = family.partition(first, last);
		recursive_sort(first, pivot, family);
		recursive_sort(pivot, last, family);
	}

public:

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
		auto family = family_t<bidirectional_iterator_t, comparator_t>(is_before);
		recursive_sort(first, last, family);
	}
};
