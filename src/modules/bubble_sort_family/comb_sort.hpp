/*
 * Shrink factor (Hệ số co) = (1 - e^(-φ))^(-1) ≈ 1.3
 * found by Stephen Lacey and Richad Bo
 */

#pragma once

#include "bubble_sort.hpp"

namespace mak
{
	class comb_sort;
}

class mak::comb_sort : public mak::base_sorting_algorithm<
	mak::comb_sort,
	mak::bubble_sort_family,
	std::bidirectional_iterator_tag
>
{
private:
	static auto get_gap_sequence(std::uint64_t first_value)
	{
		std::list gap_sequence{ first_value };
		for (auto gap = (first_value * 10) / 13; gap >= 2; gap = (gap * 10) / 13)
			gap_sequence.emplace_back(gap);
		return gap_sequence;
	}

public:
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> bidirectional_iterator_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
	static constexpr void
	sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		auto d_first_last = ranges::distance(first, --last);
		auto gap_sequence = get_gap_sequence(d_first_last);

		for (auto const& gap : gap_sequence)
		{
			auto [cur_first, cur_last] = std::pair(first, last);
			auto upper_limit = ranges::prev(last, gap - 1);
			auto d_cur_first_last = d_first_last;

			while (cur_first != upper_limit)
			{
				cur_last =
					(cur_last != last) ?
					ranges::next(cur_last) :
					ranges::prev(last, d_cur_first_last % gap);

				family.sort_subrange({
						.first = cur_first,
						.last = cur_last,
						.gap_opt = gap
					});

				++cur_first;
				--d_cur_first_last;
			}
		}

		bubble_sort::sort(first, ++last, is_before);
	}
};
