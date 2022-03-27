#pragma once

#include "sorting_algorithm.abstract.hpp"
#include "types/integer.type.hpp"

#include <forward_list>

namespace mak
{
	using mak::types::make_unsigned_t;

	template<
		std::forward_iterator iterator_t,
		concepts::iter_comparator<iterator_t> comparator_t
	> class insertion_sort_family;
}

template<
	std::forward_iterator iterator_t,
	mak::concepts::iter_comparator<iterator_t> comparator_t
>
class mak::insertion_sort_family
{
private:
	using forward_iterator_t = iterator_t;
	using bidirectional_iterator_t = iterator_t;

	static inline auto transform_to_2_way =
		transform_to_2_way<iterator_t, comparator_t>;

	std::invoke_result_t<decltype(transform_to_2_way), comparator_t> is_before;

	void rotate_right
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		make_unsigned_t<bidirectional_iterator_t> gap
	) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		auto stored_value = ranges::iter_move(last);
		for (auto current = last; current != first; ) {
			auto temp = ranges::prev(current, gap);
			*current = ranges::iter_move(temp);
			current = temp;
		}
		*first = std::move(stored_value);
	}

public:
	insertion_sort_family(comparator_t const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	template <class search_function_t>
	void generic_insertion_sort
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		make_unsigned_t<bidirectional_iterator_t> gap,
		search_function_t search
	) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>&&
	std::invocable<
		search_function_t,
		bidirectional_iterator_t,
		bidirectional_iterator_t,
		decltype(is_before),
		make_unsigned_t<bidirectional_iterator_t>
	>
	{
		auto sub_last = ranges::next(first, gap);
		auto sub_first = first;
		auto d_first_sub_last = ranges::distance(first, sub_last);

		while (sub_last != last)
		{
			auto inserted_position = search(sub_first, sub_last, is_before, gap);
			rotate_right(inserted_position, sub_last, gap);

			++sub_last;
			++d_first_sub_last;
			sub_first = (d_first_sub_last % gap == 0) ? first : ranges::next(sub_first);
		}
	}

	static auto binary_search
	(
		forward_iterator_t first,
		forward_iterator_t last,
		decltype(is_before) is_before,
		make_unsigned_t<forward_iterator_t> gap
	)
	{
		if (gap == 1) {
			return ranges::upper_bound(first, last, *last, is_before);
		}

		// TODO: handle case - gap > 1
		return first;
	}

	static auto reverse_linear_search
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		decltype(is_before) is_before,
		make_unsigned_t<bidirectional_iterator_t> gap
	)
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		auto current = ranges::prev(last, gap);
		while (current != first and is_before(*last, *current)) {
			current = ranges::prev(current, gap);
		}
		return is_before(*last, *current) ? current : ranges::next(current, gap);
	}
};
