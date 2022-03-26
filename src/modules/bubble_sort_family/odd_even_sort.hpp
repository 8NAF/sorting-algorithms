#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range	

	struct odd_even_sort;
	using brick_sort = odd_even_sort;
}

struct mak::odd_even_sort : mak::base_sorting_algorithm<
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

		auto family = family_t<Bidi_It, Comparator>(is_before, 2, 1);

		auto sort_even = [&family](auto&& first, auto&& last, bool& not_swapped)
		{
			family.sort_the_rest({
					.first = first,
					.last = last,
					.is_break_on_first_swap = [&](auto const& current) {
						not_swapped = false;
						family.sort_the_rest({ ranges::next(current, 2), last });
						return true;
					}
				});
		};
		auto sort_odd = [&sort_even, &family](auto&& first, auto&& last, bool& not_swapped) {
			not_swapped ?
				sort_even(first, last, not_swapped) :
				family.sort_the_rest({ first, last });
		};

		bool mod2 = ranges::distance(first, last) % 2;
		auto [first_even, last_even] = std::pair(first, ranges::prev(last, mod2));
		auto [first_odd, last_odd] = std::pair(ranges::next(first), ranges::prev(last, not mod2));

		for (bool not_swapped = true; true; not_swapped = true) {
			sort_even(first_even, last_even, not_swapped);
			sort_odd(first_odd, last_odd, not_swapped);
			if (not_swapped) return;
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
