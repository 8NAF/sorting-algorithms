#pragma once

#include <iterator>

namespace mak
{
#define input_it_t input_iterator_t
#define bidi_it_t bidirectional_iterator_t

	namespace ranges = std::ranges;

	namespace functions
	{
		template <std::input_iterator input_it_t>
		constexpr auto midpoint(input_it_t first, input_it_t last) {
			return ranges::next(first, ranges::distance(first, last) / 2);
		}

		template <std::input_iterator input_it_t>
		constexpr auto prev
		(
			input_it_t from,
			input_it_t target,
			std::iter_difference_t<input_it_t> n = 1
		)
		{
			if (n == 0) {
				return target;
			}

			if constexpr (std::bidirectional_iterator<input_it_t>) {
				return ranges::prev(target, n);
			}
			else {
				return ranges::next(from, ranges::distance(from, target) - n);
			}
		}
	}

#undef input_it_t
#undef bidi_it_t
}
