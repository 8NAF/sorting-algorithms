#pragma once

#include <iterator>
#include <compare>

namespace mak
{
	namespace concepts
	{
		template <class F>
		concept three_way_comparator = std::predicate<F, std::partial_ordering>;

		template <class F, class T>
		concept two_way_comparator = std::predicate<F, T, T>;

		template <class F, class It>
		concept iter_two_way_comparator =
			(std::input_or_output_iterator<It> || std::ranges::range<It>) &&
			two_way_comparator<F, std::iter_value_t<It>>;

		template <class F, class T>
		concept comparator = three_way_comparator<F> ||
			two_way_comparator<F, T>;

		template <class F, class It>
		concept iter_comparator = three_way_comparator<F> ||
			iter_two_way_comparator<F, It>;
	}
}
