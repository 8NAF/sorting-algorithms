#pragma once

#include "family.hpp"

namespace mak
{
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	struct quick_sort;
	using recursive_quick_sort = quick_sort;
};

class mak::quick_sort : mak::base_sorting_algorithm<
	mak::quick_sort_family
>
{
private:
	template <
		quick_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t
	> static void recursive_sort
	(
		iterator_t first,
		iterator_t last,
		family_t<iterator_t, comparator_t> const& family
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto pivot = family.partition(first, last);
		recursive_sort(first, pivot, family);
		recursive_sort(pivot, last, family);
	}

public:

	template <
		quick_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		comparator_t is_before = {}
	)
	{
		auto family = family_t<iterator_t, comparator_t>(is_before);
		recursive_sort(first, last, family);
	}

	template <
		quick_sort_family_cp::range range_t,
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
