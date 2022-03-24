#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	class quick_sort;
	using recursive_quick_sort = quick_sort;
};

class mak::quick_sort : mak::quick_sort_family
{
private:
	template <
		std::bidirectional_iterator Bidi_It,
		two_way_comparator<std::iter_value_t<Bidi_It>> Comparator
	> static void recursive_sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto pivot = partition(first, last, is_before);
		recursive_sort(first, pivot, is_before);
		recursive_sort(pivot, last, is_before);
	}

public:

	template <
		std::bidirectional_iterator Bidi_It,
		comparator<std::iter_value_t<Bidi_It>> Comparator = default_comparator
	> static void sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before = default_comparator()
	)
	{
		using value_t = std::iter_value_t<Bidi_It>;
		auto is_before_2_way = transform_to_2_way<value_t>(is_before);

		recursive_sort(first, last, is_before_2_way);
	}

	template <
		ranges::bidirectional_range Bidi_Rn,
		comparator<std::iter_value_t<Bidi_Rn>> Comparator = default_comparator
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
		comparator<std::iter_value_t<Pointer>> Comparator = default_comparator
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
