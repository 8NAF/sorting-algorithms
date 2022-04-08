/*
 * Shrink factor (Hệ số co) = (1 - e^(-φ))^(-1) ≈ 1.3
 * found by Stephen Lacey and Richad Bo
 */

#pragma once

#include "bubble_sort.hpp"
#include "adaptors/cyclic_iterator.adaptor.hpp"

namespace mak
{
	using adaptors::cyclic_iterator;
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
			if (gap >= d_first_last) continue;

			auto head = cyclic_iterator(first, ranges::next(first, gap));

			auto mod = d_first_last % gap;
			auto current_tail = ranges::prev(last, mod);
			auto tail = cyclic_iterator(
				ranges::prev(current_tail, gap - mod - 1),
				last,
				current_tail
			);

			while (head.is_not_last())
			{
				family.sort_subrange({
					.first = head,
					.last = tail,
					.gap_opt = gap
				});

				++head;
				++tail;
			}
		}

		bubble_sort::sort(first, ++last, is_before);
	}
};
