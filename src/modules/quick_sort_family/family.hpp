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
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	using mak::functions::midpoint;

	// for including header file
	using mak::concepts::iter_two_way_comparator;
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;
	using mak::functions::transform_to_2_way;

	namespace quick_sort_family_cp
	{
		template <class iterator_t>
		concept iterator = std::bidirectional_iterator<iterator_t>;
		template <class range_t>
		concept range = ranges::bidirectional_range<range_t>;
	}

	template<
		quick_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t
	> class quick_sort_family;
}

template<
	mak::quick_sort_family_cp::iterator iterator_t,
	mak::concepts::iter_comparator<iterator_t> comparator_t
>
class mak::quick_sort_family
{

private:

	friend class intro_sort;

	static inline auto transform_to_2_way =
		transform_to_2_way<iterator_t, comparator_t>;

	std::invoke_result_t<decltype(transform_to_2_way), comparator_t> is_before;

public:

	quick_sort_family(comparator_t const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	auto partition(iterator_t first, iterator_t last) const
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
#undef iterator_t
#undef range_t
}
