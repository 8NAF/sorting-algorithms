#pragma once

#include "family.hpp"
#include "modules/insertion_sort_family/insertion_sort.hpp"
#include "modules/heap_sort_family/heap_sort.hpp"
#include "modules/quick_sort_family/family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	class intro_sort;
	using introspective_sort = intro_sort;
};

class mak::intro_sort : mak::base_sorting_algorithm<
	mak::hybrid_sort_family
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
		quick_sort_family<Bidi_It, Comparator> const& qs_family,
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
		std::bidirectional_iterator Bidi_It,
		iter_comparator<Bidi_It> Comparator = default_comparator
	> static void sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before = default_comparator()
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto qs_family = quick_sort_family<Bidi_It, Comparator>(is_before);
		std::size_t max_depth = std::log(ranges::distance(first, last)) * 2;

		recursive_sort(first, last, qs_family, max_depth);
	}

	template <
		ranges::bidirectional_range Bidi_Rn,
		iter_comparator<Bidi_Rn> Comparator = default_comparator
	> static void sort
	(
		Bidi_Rn& range,
		Comparator is_before = default_comparator()
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
		Comparator is_before = default_comparator()
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
