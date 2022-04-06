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
	struct shell_sort;
}

struct mak::shell_sort : private mak::base_sorting_algorithm<
	mak::shell_sort,
	mak::insertion_sort_family,
	std::bidirectional_iterator_tag
>
{
	using tag_t = base_sorting_algorithm::tag_t;

	template <
		tag_to_iterator<tag_t> bidirectional_iterator_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection,
		std::invocable<std::uint64_t> gap_sequence_function = default_gap_sequence_function
	>
	requires sortable<bidirectional_iterator_t, comparator_t, projection_t>
		&& std::ranges::range<std::invoke_result_t<gap_sequence_function, std::uint64_t>>
	static constexpr void
	sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		comparator_t is_before = {},
		projection_t projection = {},
		gap_sequence_function get_gap_sequence = get_Sedgewick_1982_gap_sequence
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<
			bidirectional_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		const uint64_t d_first_last = ranges::distance(first, last);
		auto gap_sequence = get_gap_sequence(n);

		for (auto& gap : gap_sequence)
		{
			if (gap >= d_first_last) continue;

			family.generic_insertion_sort(
				first,
				last,
				gap,
				decltype(family)::reverse_linear_search
			);
		}
	}

	template <
		tag_to_range<tag_t> range_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection,
		std::invocable<std::uint64_t> gap_sequence_function = default_gap_sequence_function
	>
	requires sortable<ranges::iterator_t<range_t>, comparator_t, projection_t>
		&& std::ranges::range<std::invoke_result_t<gap_sequence_function, std::uint64_t>>
	static constexpr void
	sort
	(
		range_t& range,
		comparator_t is_before = {},
		projection_t projection = {},
		gap_sequence_function get_gap_sequence = get_Sedgewick_1982_gap_sequence
	)
	{
		sort(
			ranges::begin(range),
			ranges::end(range),
			is_before,
			projection,
			get_gap_sequence
		);
	}

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

	static auto get_Ciura_2001_gap_sequence(std::uint64_t)
	{
		return std::forward_list{ 701, 301, 132, 57, 23, 10, 4, 1 };
	}

	static auto get_Shell_1959_gap_sequence(std::uint64_t limit)
	{
		std::list<std::uint64_t> gap_sequence;
		for (auto pow_of2 = 2ULL; pow_of2 < limit; pow_of2 <<= 1ULL) {
			gap_sequence.emplace_back(limit / pow_of2);
		}
		return gap_sequence;
	}
};
