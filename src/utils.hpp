#pragma once

#include "concepts/comparator.concept.hpp"
#include "types/default.type.hpp"

#include <functional>
#include <ranges>

namespace mak
{
#define Input_It Input_Iterator
#define Bidi_It Bidirectional_Iterator

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
			std::input_or_output_iterator It,
			iter_comparator<It> Comparator
		> generic_comparator<std::iter_value_t<It>>
			transform_to_2_way(Comparator const& comparator)
		{
			return [comparator](auto const& lhs, auto const& rhs) constexpr {
				if constexpr (three_way_comparator<Comparator>) {
					return comparator(lhs <=> rhs);
				}
				else {
					return comparator(lhs, rhs);
				}
			};
		}

		template <std::input_iterator Input_It>
		auto midpoint(Input_It first, Input_It last) {
			return ranges::next(first, ranges::distance(first, last) / 2);
		}
	}

#undef Input_It
#undef Bidi_It
}
