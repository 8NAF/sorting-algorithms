#pragma once

#include "family.abstract.hpp"

#include <stack>

namespace mak
{
	template<class iterator_t, class comparator_t, class projection_t>
	class quick_sort_family;
}

template<class iterator_t, class comparator_t, class projection_t>
class mak::quick_sort_family
	: private mak::base_family<iterator_t, comparator_t, projection_t>
{
private:
	using forward_iterator_t = iterator_t;
	using bidirectional_iterator_t = iterator_t;

	friend class intro_sort;

public:
	using base_family = base_family<iterator_t, comparator_t, projection_t>;
	using base_family::base_family;

	constexpr auto
	partition
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
			while (this->is_before(*left, middle_value)) {
				++left;
			}
			while (this->is_before(middle_value, *right)) {
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
