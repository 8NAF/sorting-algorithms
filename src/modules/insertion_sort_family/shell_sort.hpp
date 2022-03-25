/* Gap sequences (source https://en.wikipedia.org/wiki/Shellsort#Gap_sequences):
	#01. Shell, 1959
	#02. Frank & Lazarus, 1960
	#03. Hibbard, 1963
	#04. Papernov & Stasevich, 1965
	#05. Pratt, 1971
	#06. Knuth, 1971
		 Pratt, 1971
	#07. Incerpi & Sedgewick, 1985
		 Knuth, 1985
	#08. Sedgewick, 1982
	#09. Sedgewick, 1986
	#10. Gonnet & Baeza-Yates, 1991
	#11. Tokuda, 1992
	#12. Ciura, 2001
*/

/* Details:
	- 1. Ciura's gap sequences (#12) is the best,
		 but the general formula has not been found yet:
		=> 1, 4, 10, 23, 57, 132, 301, 701, 1750

	- 3. The most commonly used gap sequence is Sedgewick, 1982 (#08):
		4^k + 3 * 2^(k - 1) + 1, prefixed with 1 and k starts at 1
		or (4 * 2^k * 2^k) + (3 * 2^k) + (1), k starts at 0
		or 4 * x * x + 3 * x + 1, x = 2^k (k starts at 0)
*/

#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	class shell_sort;
};

struct mak::shell_sort : mak::insertion_sort_family
{
	static auto get_Sedgewick_1982_gap_sequence(std::uint64_t limit)
	{
		std::forward_list <std::uint64_t> gap_sequence{ 1ULL };
		for (auto pow_of2 = 1ULL; true; pow_of2 <<= 1ULL)
		{
			auto next_gap = 4ULL * pow_of2 * pow_of2 + 3ULL * pow_of2 + 1ULL;
			if (next_gap >= limit) {
				return gap_sequence;
			}
			gap_sequence.emplace_front(next_gap);
		}
	}

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
		comparator_t is_before_2_way = transform_to_2_way<value_t>(is_before);

		auto gap_sequence = get_Sedgewick_1982_gap_sequence(
			ranges::distance(first, last)
		);
		for (auto& gap : gap_sequence) {

			generic_insertion_sort(
				first,
				last,
				is_before_2_way,
				gap,
				reverse_linear_search<Bidi_It, comparator_t>
			);
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
