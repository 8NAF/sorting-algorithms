#pragma once

#include "concepts/comparator.concept.hpp"

// only for including header file
#include "utils.hpp"
#include "types/default.type.hpp"

#include <iterator>
#include <algorithm>
#include <utility>
#include <stack>

namespace mak
{

#define Bidi_It Bidirectional_Iterator

	class quick_sort_family;

	namespace ranges = std::ranges;
	using mak::functions::midpoint;

	// for including header file
	using mak::concepts::two_way_comparator;
	using mak::concepts::comparator;
	using mak::types::default_comparator;
	using mak::functions::no_need_to_sort;
	using mak::functions::transform_to_2_way;
}

class mak::quick_sort_family
{
protected:

	template <
		std::bidirectional_iterator Bidi_It,
		two_way_comparator<std::iter_value_t<Bidi_It>> Comparator
	> static auto partition
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before
	)
	{
		auto middle_value = *midpoint(first, last);
		auto [left, right] = std::pair(first, ranges::prev(last));

		while (true)
		{
			while (is_before(*left, middle_value)) {
				++left;
			}
			while (is_before(middle_value, *right)) {
				--right;
			}

			// left >= right
			if (ranges::distance(first, left) >= ranges::distance(first, right)) {
				return left;
			}

			ranges::iter_swap(left, right);
			++left, --right;
		}
	}

	friend class intro_sort;
};

namespace mak
{
#undef Bidi_It
}
