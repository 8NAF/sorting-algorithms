#pragma once

#include "family.hpp"
#include "modules/insertion_sort_family/insertion_sort.hpp"
#include "modules/heap_sort_family/heap_sort.hpp"
#include "modules/quick_sort_family/family.hpp"

namespace mak
{
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	class intro_sort;
	using introspective_sort = intro_sort;
};

class mak::intro_sort : mak::base_sorting_algorithm<
	mak::hybrid_sort_family
>
{
private:
	template <
		hybrid_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t
	> static void recursive_sort
	(
		iterator_t first,
		iterator_t last,
		quick_sort_family<iterator_t, comparator_t> const& qs_family,
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
	template <
		hybrid_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto qs_family = quick_sort_family<iterator_t, comparator_t>(is_before);
		std::size_t max_depth = std::log(ranges::distance(first, last)) * 2;

		recursive_sort(first, last, qs_family, max_depth);
	}

	template <
		hybrid_sort_family_cp::range range_t,
		iter_comparator<range_t> comparator_t = default_comparator
	> static void sort
	(
		range_t& range,
		comparator_t is_before = {}
	)
	{
		sort(ranges::begin(range), ranges::end(range), is_before);
	}

	template <
		class pointer_t,
		iter_comparator<pointer_t> comparator_t = default_comparator
	> static void sort
	(
		pointer_t pointer,
		std::size_t n,
		comparator_t is_before = {}
	) requires std::is_pointer_v<pointer_t>
	{
		sort(pointer, pointer + n, is_before);
	}
};

namespace mak
{
#undef iterator_t
#undef range_t
}
