#pragma once

#include <compare>

namespace mak
{
	namespace concepts
	{
		template <class F, class T>
		concept two_way_comparator = std::predicate<F, T, T>;

		template <class F>
		concept three_way_comparator = std::predicate<F, std::partial_ordering>;

		template <class F, class T>
		concept comparator = three_way_comparator<F> || two_way_comparator<F, T>;
	}
}
