#pragma once

#include <iterator>

namespace mak
{
	namespace ranges = std::ranges;

	namespace functions
	{
		template <std::input_iterator input_iterator_t>
		constexpr auto
		midpoint
		(
			input_iterator_t first,
			std::sentinel_for<input_iterator_t> auto last
		)
		{
			return ranges::next(first, ranges::distance(first, last) / 2);
		}

		template <std::input_iterator input_iterator_t>
		constexpr auto prev
		(
			input_iterator_t from,
			input_iterator_t target,
			std::iter_difference_t<input_iterator_t> n = 1
		)
		{
			if (n == 0) {
				return target;
			}

			if constexpr (std::bidirectional_iterator<input_iterator_t>) {
				return ranges::prev(target, n);
			}
			else {
				return ranges::next(from, ranges::distance(from, target) - n);
			}
		}
	}
}
