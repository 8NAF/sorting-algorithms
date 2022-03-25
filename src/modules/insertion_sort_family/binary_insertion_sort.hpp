#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	class binary_insertion_sort;
};

struct mak::binary_insertion_sort : mak::insertion_sort_family
{
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
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<Bidi_It>;
		using comparator_t = generic_comparator<value_t>;
		comparator_t is_before_2_way = transform_to_2_way<value_t>(is_before);

		generic_insertion_sort(
			first,
			last,
			is_before_2_way,
			1,
			binary_search<Bidi_It, comparator_t>
		);
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
