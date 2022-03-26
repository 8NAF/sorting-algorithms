#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	struct quick_sort;
	using recursive_quick_sort = quick_sort;
};

class mak::quick_sort : mak::base_sorting_algorithm<
	mak::quick_sort_family
>
{
private:
	template <
		std::bidirectional_iterator Bidi_It,
		iter_comparator<Bidi_It> Comparator
	> static void recursive_sort
	(
		Bidi_It first,
		Bidi_It last,
		family_t<Bidi_It, Comparator> const& family
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto pivot = family.partition(first, last);
		recursive_sort(first, pivot, family);
		recursive_sort(pivot, last, family);
	}

public:

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
		auto family = family_t<Bidi_It, Comparator>(is_before);
		recursive_sort(first, last, family);
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
