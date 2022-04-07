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

	namespace types
	{
		template <std::input_iterator iterator_t>
		struct limit : private std::pair<iterator_t, iterator_t>
		{
			constexpr limit(iterator_t lower, iterator_t upper)
				: std::pair<iterator_t, iterator_t>(lower, upper)
			{}

			iterator_t const& lower = this->first;
			iterator_t const& upper = this->second;

			constexpr auto next(iterator_t current) {
				return current == upper ? lower : ranges::next(current);
			}
		};
	}

#undef input_it_t
#undef bidi_it_t
}
