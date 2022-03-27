#pragma once

#include "family.hpp"

namespace mak
{
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	struct cocktail_shaker_sort;

	using cocktail_sort = cocktail_shaker_sort;
	using shaker_sort = cocktail_shaker_sort;
	using bidirectional_bubble_sort = cocktail_shaker_sort;
	using ripple_sort = cocktail_shaker_sort;
	using shuffle_sort = cocktail_shaker_sort;
	using shuttle_sort = cocktail_shaker_sort;
}

struct mak::cocktail_shaker_sort : mak::base_sorting_algorithm<
	mak::bubble_sort_family
>
{
	template <
		std::bidirectional_iterator iterator_t,
		iter_comparator<iterator_t> comparator_t = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<iterator_t, comparator_t>(is_before);
		for (--last; first != last; )
		{
			auto last_swap = family.find_last_swap(first, last);
			if (bool not_swapped = (last_swap == first); not_swapped) return;
			last = last_swap;

			last_swap = family.reverse_find_last_swap(first, last);
			if (bool not_swapped = (last_swap == last); not_swapped) return;
			first = last_swap;
		}
	}

	template <
		ranges::bidirectional_range range_t,
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
