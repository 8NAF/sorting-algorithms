/*
 * Shrink factor (Hệ số co) = (1 - e^(-φ))^(-1) ≈ 1.3
 * found by Stephen Lacey and Richad Bo
 */

#pragma once

#include "bubble_sort.hpp"

namespace mak
{
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	class comb_sort;
};

class mak::comb_sort : mak::base_sorting_algorithm<
	mak::bubble_sort_family
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

		auto family = family_t<iterator_t, comparator_t>(is_before);

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
