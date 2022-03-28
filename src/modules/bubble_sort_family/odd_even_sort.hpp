#pragma once

#include "family.hpp"

namespace mak
{
	struct odd_even_sort;
	using brick_sort = odd_even_sort;
}

struct mak::odd_even_sort : mak::base_sorting_algorithm<
	mak::odd_even_sort,
	mak::bubble_sort_family,
	std::forward_iterator_tag
>
{
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> forward_iterator_t,
		iter_comparator<forward_iterator_t> comparator_t = default_comparator
	> static void sort
	(
		forward_iterator_t first,
		forward_iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<forward_iterator_t, comparator_t>(is_before, 2, 1);

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
		auto [last_even, last_odd] = std::pair(
			prev(first, last, mod2),
			prev(first, last, not mod2)
		);
		auto [first_even, first_odd] = std::pair(first, ranges::next(first));

		for (bool not_swapped = true; true; not_swapped = true) {
			sort_even(first_even, last_even, not_swapped);
			sort_odd(first_odd, last_odd, not_swapped);
			if (not_swapped) return;
		}
	}
};
