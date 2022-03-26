#pragma once

#include "concepts/comparator.concept.hpp"
#include "utils.hpp"

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "types/default.type.hpp"

namespace mak
{

#define Input_It Input_Iterator
#define Bidi_It Bidirectional_Iterator

	using mak::functions::transform_to_2_way;

	// for including header file
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;

	template<
		std::bidirectional_iterator Bidi_It,
		iter_comparator<Bidi_It> Comparator
	> class heap_sort_family;
}

template<
	std::bidirectional_iterator Bidi_It,
	mak::concepts::iter_comparator<Bidi_It> Comparator
>
class mak::heap_sort_family
{
private:

	static inline auto transform_to_2_way =
		transform_to_2_way<Bidi_It, Comparator>;

	std::invoke_result_t<decltype(transform_to_2_way), Comparator> is_before;
public:

	heap_sort_family(Comparator const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	// require input_iterator
	void heapify(Bidi_It first, Bidi_It last, Bidi_It root) const
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

	void make_heap(Bidi_It first, Bidi_It last) const
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

	void do_sort(Bidi_It first, Bidi_It last) const
	{
		for (--last; last != first; --last)
		{
			ranges::iter_swap(first, last);
			heapify(first, last, first);
		}
	}
};

namespace mak
{
#undef Input_It
#undef Bidi_It
}
