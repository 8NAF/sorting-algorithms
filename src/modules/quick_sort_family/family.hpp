#pragma once

#include "concepts/comparator.concept.hpp"

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <iterator>
#include <algorithm>
#include <utility>
#include <stack>

namespace mak
{

#define Bidi_It Bidirectional_Iterator

	using mak::functions::midpoint;

	// for including header file
	using mak::concepts::iter_two_way_comparator;
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;
	using mak::functions::transform_to_2_way;

	template<
		std::bidirectional_iterator Bidi_It,
		iter_comparator<Bidi_It> Comparator
	> class quick_sort_family;
}

template<
	std::bidirectional_iterator Bidi_It,
	mak::concepts::iter_comparator<Bidi_It> Comparator
>
class mak::quick_sort_family
{

private:

	friend class intro_sort;

	static inline auto transform_to_2_way =
		transform_to_2_way<Bidi_It, Comparator>;

	std::invoke_result_t<decltype(transform_to_2_way), Comparator> is_before;

public:

	quick_sort_family(Comparator const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	auto partition(Bidi_It first, Bidi_It last) const
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
};

namespace mak
{
#undef Bidi_It
}
