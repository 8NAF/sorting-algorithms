#pragma once

#include "family.hpp"

namespace mak
{
	struct cycle_sort;
}

struct mak::cycle_sort : mak::base_sorting_algorithm<
	mak::cycle_sort,
	mak::cycle_sort_family,
	std::bidirectional_iterator_tag
>
{
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> bidirectional_iterator_t,
		std::sentinel_for<bidirectional_iterator_t> sentinel_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
	static constexpr auto
	sort
	(
		bidirectional_iterator_t first,
		sentinel_t sentinel,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		auto o_last = get_last_iterator(first, sentinel);
		if (no_need_to_sort(first, o_last)) return o_last;

		auto family = family_t<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		for (auto last = ranges::prev(o_last); last != first; --last)
		{
			auto const& last_value = *last;
			while (true)
			{
				auto n_after_last = ranges::count_if(
					first,
					last,
					[&](auto const& current_value) {
						return family.is_before(last_value, current_value);
					}
				);
				if (0 == n_after_last) break;

				auto expected_position = ranges::prev(last, n_after_last);
				for (; *expected_position == last_value; --expected_position);
				ranges::iter_swap(expected_position, last);
			}
		}

		return o_last;
	}
};
