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
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	struct shell_sort;
};

struct mak::shell_sort : mak::base_sorting_algorithm<
	mak::insertion_sort_family
>
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
		insertion_sort_family_cp::iterator iterator_t,
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
		auto gap_sequence = get_Sedgewick_1982_gap_sequence(
			ranges::distance(first, last)
		);

		for (auto& gap : gap_sequence)
		{
			family.generic_insertion_sort(
				first,
				last,
				gap,
				decltype(family)::reverse_linear_search
			);
		}
	}

	template <
		insertion_sort_family_cp::range range_t,
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
