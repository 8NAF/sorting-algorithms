#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

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
		std::bidirectional_iterator Bidi_It,
		iter_comparator<Bidi_It> Comparator = default_comparator
	> static void sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<Bidi_It, Comparator>(is_before);
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
		ranges::bidirectional_range Bidi_Rn,
		iter_comparator<Bidi_Rn> Comparator = default_comparator
	> static void sort
	(
		Bidi_Rn& range,
		Comparator is_before = {}
	)
	{
		sort(ranges::begin(range), ranges::end(range), is_before);
	}

	template <
		class Pointer,
		iter_comparator<Pointer> Comparator = default_comparator
	> static void sort
	(
		Pointer pointer,
		std::size_t n,
		Comparator is_before = {}
	) requires std::is_pointer_v<Pointer>
	{
		sort(pointer, pointer + n, is_before);
	}
};

namespace mak
{
#undef Bidi_It
#undef Bidi_Rn
}
