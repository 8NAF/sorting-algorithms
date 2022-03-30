#pragma once

#include "concepts/comparator.concept.hpp"
#include "types/function.type.hpp"

#include <functional>
#include <iterator>

namespace mak
{
#define input_it_t input_iterator_t
#define bidi_it_t bidirectional_iterator_t

	namespace ranges = std::ranges;
	using mak::concepts::comparator;
	using mak::concepts::iter_comparator;
	using mak::concepts::three_way_comparator;
	using mak::types::generic_comparator;

	namespace functions
	{
		/**
		  * Transform a (3-way or 2-way) comparator to a 2-way comparator
		  */
		template <
			std::input_iterator iterator_t,
			iter_comparator<iterator_t> comparator_t
		> generic_comparator<std::iter_value_t<iterator_t>>
			transform_to_2_way(comparator_t const& comparator)
		{
			return [comparator](auto const& lhs, auto const& rhs) constexpr {
				if constexpr (three_way_comparator<comparator_t>) {
					return comparator(lhs <=> rhs);
				}
				else {
					return comparator(lhs, rhs);
				}
			};
		}

		template <std::input_iterator input_it_t>
		auto midpoint(input_it_t first, input_it_t last) {
			return ranges::next(first, ranges::distance(first, last) / 2);
		}

		template <std::input_iterator input_it_t>
		auto prev
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
