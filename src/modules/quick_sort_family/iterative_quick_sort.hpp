#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	struct iterative_quick_sort;
};

struct mak::iterative_quick_sort : mak::base_sorting_algorithm<
	mak::quick_sort_family
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

		std::stack<std::pair<Bidi_It, Bidi_It>> order;
		order.emplace(first, last);

		while (not order.empty())
		{
			auto [left, right] = order.top();
			order.pop();

			auto pivot = family.partition(left, right);

			if (not no_need_to_sort(left, pivot)) {
				order.emplace(left, pivot);
			}
			if (not no_need_to_sort(pivot, right)) {
				order.emplace(pivot, right);
			}
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
