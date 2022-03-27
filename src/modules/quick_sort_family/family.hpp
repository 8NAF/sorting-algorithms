#pragma once

#include "sorting_algorithm.abstract.hpp"

#include <stack>

namespace mak
{
	template<
		std::forward_iterator iterator_t,
		iter_comparator<iterator_t> comparator_t
	> class quick_sort_family;
}

template<
	std::forward_iterator iterator_t,
	mak::concepts::iter_comparator<iterator_t> comparator_t
>
class mak::quick_sort_family
{
private:
	using forward_iterator_t = iterator_t;
	using bidirectional_iterator_t = iterator_t;

	friend class intro_sort;

	static inline auto transform_to_2_way =
		transform_to_2_way<iterator_t, comparator_t>;

	std::invoke_result_t<decltype(transform_to_2_way), comparator_t> is_before;

public:
	quick_sort_family(comparator_t const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	auto partition
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last
	) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>
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
