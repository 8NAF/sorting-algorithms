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
		iter_comparator<bidirectional_iterator_t> comparator_t = default_comparator
	> static void sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<bidirectional_iterator_t, comparator_t>(is_before);

		auto d_first_last = ranges::distance(first, --last);
		auto gap_sequence = get_gap_sequence(d_first_last);

		for (auto const& gap : gap_sequence)
		{
			auto [sub_first, sub_last] = std::pair(first, last);
			auto upper_limit = ranges::prev(last, gap - 1);
			auto d_sub_first_Last = d_first_last;

			while (sub_first != upper_limit)
			{
				sub_last =
					(sub_last != last) ?
					ranges::next(sub_last) :
					ranges::prev(last, d_sub_first_Last % gap);

				family.sort_the_rest({
						.first = sub_first,
						.last = sub_last,
						.gap_opt = gap
					});

				++sub_first;
				--d_sub_first_Last;
			}
		}

		bubble_sort::sort(first, ++last, is_before);
	}
};
