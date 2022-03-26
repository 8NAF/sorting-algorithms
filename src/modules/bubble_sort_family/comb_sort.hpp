/*
 * Shrink factor (Hệ số co) = (1 - e^(-φ))^(-1) ≈ 1.3
 * found by Stephen Lacey and Richad Bo
 */

#pragma once

#include "bubble_sort.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

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
						.gap = gap
					});

				++sub_first;
				--d_sub_first_Last;
			}
		}

		bubble_sort::sort(first, ++last, is_before);
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
