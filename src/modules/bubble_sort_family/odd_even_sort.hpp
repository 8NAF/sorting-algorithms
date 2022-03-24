#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range	

	class odd_even_sort;
	using brick_sort = odd_even_sort;
}

struct mak::odd_even_sort : mak::bubble_sort_family
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
		using break_function_t = generic_break_function<Bidi_It>;

		auto is_before_2_way = transform_to_2_way<value_t>(is_before);
		auto _sort_the_rest = [&is_before_2_way]
		(
			Bidi_It first,
			Bidi_It last,
			break_function_t is_break_on_first_swap = default_break_function
			)
		{
			sort_the_rest<Bidi_It, comparator_t>({
					.first = first,
					.last = last,
					.is_before = is_before_2_way,
					.gap = 2,
					.step = 1,
					.is_break_on_first_swap = is_break_on_first_swap
				});
		};

		auto sort_even = [&_sort_the_rest](auto&& first, auto&& last, bool& not_swapped)
		{
			auto is_break_on_first_swap = [&](auto&& current)
			{
				not_swapped = false;
				_sort_the_rest(ranges::next(current, 2), last);
				return true;
			};
			_sort_the_rest(first, last, is_break_on_first_swap);
		};
		auto sort_odd = [&sort_even, &_sort_the_rest](auto&& first, auto&& last, bool& not_swapped) {
			not_swapped ? sort_even(first, last, not_swapped) : _sort_the_rest(first, last);
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
