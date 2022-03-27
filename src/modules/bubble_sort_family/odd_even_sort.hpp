#pragma once

#include "family.hpp"

namespace mak
{
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t	

	struct odd_even_sort;
	using brick_sort = odd_even_sort;
}

struct mak::odd_even_sort : mak::base_sorting_algorithm<
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

		auto family = family_t<iterator_t, comparator_t>(is_before, 2, 1);

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
