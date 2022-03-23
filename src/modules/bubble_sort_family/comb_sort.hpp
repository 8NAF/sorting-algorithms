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

class mak::comb_sort : mak::bubble_sort_family
{

private:

	template <std::signed_integral Int>
	static auto get_gap_sequence(Int first_value)
	{
		std::list<std::uint64_t> gap_sequence{ (std::uint64_t)first_value };
		for (auto gap = (first_value * 10) / 13; gap >= 2; gap = (gap * 10) / 13)
			gap_sequence.emplace_back(gap);
		return gap_sequence;
	}

public:

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
		using comparator_t = std::invoke_result_t<
			decltype(transform_to_2_way<value_t, Comparator>),
			Comparator
		>;

		auto is_before_2_way = transform_to_2_way<value_t>(is_before);
		auto _sort_the_rest = sort_the_rest<Bidi_It, comparator_t>;

		auto gap_sequence = get_gap_sequence(ranges::distance(first, --last));
		for (auto const& gap : gap_sequence)
		{
			for (auto lower_limit = first; lower_limit != last; ++lower_limit)
			{
				auto upper_limit = ranges::prev(last, ranges::distance(lower_limit, last) % gap);
				_sort_the_rest({ lower_limit, upper_limit, is_before_2_way, gap });
			}
		}

		bubble_sort::sort(first, ++last, is_before);
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
