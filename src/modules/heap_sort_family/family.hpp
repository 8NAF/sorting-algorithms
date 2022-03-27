#pragma once

#include "sorting_algorithm.abstract.hpp"

namespace mak
{
	template<
		std::forward_iterator iterator_t,
		iter_comparator<iterator_t> comparator_t
	> class heap_sort_family;
}

template<
	std::forward_iterator iterator_t,
	mak::concepts::iter_comparator<iterator_t> comparator_t
>
class mak::heap_sort_family
{
private:
	using forward_iterator_t = iterator_t;
	using bidirectional_iterator_t = iterator_t;

	static inline auto transform_to_2_way =
		transform_to_2_way<iterator_t, comparator_t>;

	std::invoke_result_t<decltype(transform_to_2_way), comparator_t> is_before;

public:
	heap_sort_family(comparator_t const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	void heapify
	(
		forward_iterator_t first,
		forward_iterator_t last,
		forward_iterator_t root
	) const
	{
		auto get_left_child = [&root](auto&& parent) {
			return ranges::next(root, ranges::distance(root, parent) * 2 + 1);
		};
		auto has_left_child = [&root, &last](auto&& parent)
		{
			auto from_root_to_parent = ranges::distance(root, parent);
			auto from_root_to_last = ranges::distance(root, last);

			// prevents overflowing
			// 2 * from_root_to_parent + 1 < from_root_to_last
			return from_root_to_parent + 1 < from_root_to_last - from_root_to_parent;
		};

		auto stored_value = std::move(*first);
		auto& parent = first;

		while (has_left_child(parent))
		{
			auto left_child = get_left_child(parent);
			auto right_child = ranges::next(left_child);

			auto& extreme_child = (right_child != last and is_before(*left_child, *right_child)) ?
				right_child : left_child;

			if (is_before(*extreme_child, stored_value)) break;

			*parent = std::move(*extreme_child);
			parent = extreme_child;
		}

		*parent = std::move(stored_value);
	}

	void make_heap(bidirectional_iterator_t first, bidirectional_iterator_t last) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		// The number of nodes have children in a sequence with n elements is: trunc(n div 2)
		// Since the array starts at 0, we have to subtract 1
		auto last_node_has_child = [](auto&& first, auto&& last)
		{
			auto n_nodes_have_child = ranges::distance(first, last) / 2;
			return ranges::next(first, n_nodes_have_child - 1);
		};

		for (auto current = last_node_has_child(first, last); current != first; --current) {
			heapify(current, last, first);
		}
		heapify(first, last, first);
	}

	void do_sort(bidirectional_iterator_t first, bidirectional_iterator_t last) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		for (--last; last != first; --last)
		{
			ranges::iter_swap(first, last);
			heapify(first, last, first);
		}
	}
};
