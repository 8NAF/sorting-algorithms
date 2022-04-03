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
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
	static constexpr void
	recursive_sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		family_t<bidirectional_iterator_t, comparator_t, projection_t> const& family
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

		recursive_sort(first, last, family);
	}
};
