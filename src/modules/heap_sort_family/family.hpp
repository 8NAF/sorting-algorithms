#pragma once

#include "concepts/comparator.concept.hpp"

// only for including header file
#include "utils.hpp"
#include "types/default.type.hpp"

#include <iterator>
#include <algorithm>
#include <utility>

namespace mak
{

#define Input_It Input_Iterator
#define Bidi_It Bidirectional_Iterator

	class heap_sort_family;

	namespace ranges = std::ranges;
	using mak::concepts::two_way_comparator;

	// for including header file
	using mak::concepts::comparator;
	using mak::types::default_comparator;
	using mak::functions::no_need_to_sort;
	using mak::functions::transform_to_2_way;
}

class mak::heap_sort_family
{
protected:

	template<
		std::input_iterator Input_It,
		two_way_comparator<std::iter_value_t<Input_It>> Comparator
	> static void heapify
	(
		Input_It first,
		Input_It last,
		Comparator is_before,
		Input_It root
	)
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

	template<
		std::bidirectional_iterator Bidi_It,
		two_way_comparator<std::iter_value_t<Bidi_It>> Comparator
	> static void make_heap
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before
	)
	{
		// The number of nodes have children in a sequence with n elements is: trunc(n div 2)
		// Since the array starts at 0, we have to subtract 1
		auto last_node_has_child = [](auto&& first, auto&& last)
		{
			auto n_nodes_have_child = ranges::distance(first, last) / 2;
			return ranges::next(first, n_nodes_have_child - 1);
		};

		for (auto current = last_node_has_child(first, last); current != first; --current) {
			heapify(current, last, is_before, first);
		}
		heapify(first, last, is_before, first);
	}

	template<
		std::bidirectional_iterator Bidi_It,
		two_way_comparator<std::iter_value_t<Bidi_It>> Comparator
	> static void do_sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before
	)
	{
		for (--last; last != first; --last)
		{
			ranges::iter_swap(first, last);
			heapify(first, last, is_before, first);
		}
	}
};

namespace mak
{
#undef Input_It
#undef Bidi_It
}
