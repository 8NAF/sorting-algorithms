#pragma once

#include "family.hpp"
#include "modules/insertion_sort_family/insertion_sort.hpp"
#include "modules/heap_sort_family/heap_sort.hpp"
#include "modules/quick_sort_family/family.hpp"

namespace mak
{
	class intro_sort;
	using introspective_sort = intro_sort;
}

class mak::intro_sort : public mak::base_sorting_algorithm<
	mak::intro_sort,
	mak::hybrid_sort_family,
	std::bidirectional_iterator_tag
>
{
private:
	template <
		tag_to_iterator<tag_t> bidirectional_iterator_t,
		class comparator_t,
		class projection_t
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
	static void recursive_sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		quick_sort_family<
			bidirectional_iterator_t, comparator_t, projection_t
		> const& qs_family,
		std::size_t& max_depth
	)
	{
		if (ranges::distance(first, last) < 16) {
			insertion_sort::sort(first, last, qs_family.is_before);
			return;
		}

		if (0 == max_depth) {
			heap_sort::sort(first, last, qs_family.is_before);
			return;
		}

		auto pivot = qs_family.partition(first, last);
		--max_depth;

		recursive_sort(first, pivot, qs_family, max_depth);
		recursive_sort(pivot, last, qs_family, max_depth);
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

		std::size_t max_depth = std::log(ranges::distance(first, last)) * 2;
		auto qs_family = quick_sort_family<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));
		
		recursive_sort(first, last, qs_family, max_depth);
	}
};
