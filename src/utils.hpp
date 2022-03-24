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
	using mak::concepts::three_way_comparator;
	using mak::types::generic_comparator;

	namespace functions
	{
		template <std::input_iterator Input_It>
		constexpr bool no_need_to_sort
		(
			Input_It first,
			Input_It last
		)
		{
			if constexpr (std::random_access_iterator<Input_It>) {
				return ranges::distance(first, last) < 2;
			}

			return (first == last || ++first == last);
		}

		/**
		  * Transform a (3-way or 2-way) comparator to a 2-way comparator
		  */
		template <
			class Value,
			comparator<Value> Comparator
		> generic_comparator<Value> transform_to_2_way(Comparator&& comparator)
		{
			return [&comparator](auto&& lhs, auto&& rhs) constexpr {
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
