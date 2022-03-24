#pragma once

#include "family.hpp"

namespace mak
{
#define	Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	class double_selection_sort;
	using double_ended_selection_sort = double_selection_sort;
};

struct mak::double_selection_sort : mak::selection_sort_family
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
		auto is_before_2_way = transform_to_2_way<value_t>(is_before);

		auto middle = midpoint(first, last);
		for (; first != middle; ++first)
		{
			auto [left, right] = ranges::minmax_element(first, last, is_before_2_way);
			if (bool are_all_sorted = (*left == *right); are_all_sorted) return;

			--last;
			right = (first != right) ? right : left;

			ranges::iter_swap(first, left);
			ranges::iter_swap(last, right);
		}
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
