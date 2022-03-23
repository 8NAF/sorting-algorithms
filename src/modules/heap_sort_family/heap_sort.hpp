/* -------------------- Definitions -------------------- */

// Binary Tree (Cây nhị phân):
//	- A tree whose each node has at most 2 children

// External Node (Outer Node - Terminal Node - Leaf Node) (node lá):
//	- Node has no children

// Internal Node (Inner Node - Branch Node - )
//	- Node has children

// Full Binary Tree (Cây nhị phân đầy đủ):
//	- A binary tree
//	- All nodes have 0 or 2 children

// Complete Binary Tree (Cây nhị phân hoàn chỉnh):
//	- A binary tree
//	- All nodes have two children, except the nodes at the two lowest levels
//	- The nodes at the lowest level must be filled from left to right, with no space in between

// Perfect Binary Tree (Cây nhị phân hoàn hảo):
//	- A binary tree
//	- All nodes except the leaf nodes have 2 children
//	- The height of the left and right subtrees of any node is always equal
//	  (all the leaf nodes are at the same level)

// Balanced Binary Tree (Cây nhị phân cân bằng):
//	- A binary tree
//	- The height of the left and right subtree of any node differ by not more than 1

// Degenerate (Pathological) Binary Tree (Cây nhị phân thoái hoái):
//	- A binary tree
//	- Every internal node has one child

//Heap (Binary Heap) (Đống - Đống nhị phân):
// - A complete binary tree
// - The value of any parent node in the tree is always
// - or >= its children => called Max Heap
// - or <= its children => called Min Heap

/* ----------------------------------------------------------- */

#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	class heap_sort;
};

struct mak::heap_sort : mak::heap_sort_family
{
	template <
		std::bidirectional_iterator Bidi_It,
		comparator<std::iter_value_t<Bidi_It>> Comparator = default_comparator
	> static void sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before = default_comparator()
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<Bidi_It>;
		auto is_before_2_way = transform_to_2_way<value_t>(is_before);

		make_heap(first, last, is_before_2_way);
		do_sort(first, last, is_before_2_way);
	}

	template <
		ranges::bidirectional_range Bidi_Rn,
		comparator<std::iter_value_t<Bidi_Rn>> Comparator = default_comparator
	> static void sort
	(
		Bidi_Rn& range,
		Comparator is_before = default_comparator()
	)
	{
		sort(ranges::begin(range), ranges::end(range), is_before);
	}

	template <
		class Pointer,
		comparator<std::iter_value_t<Pointer>> Comparator = default_comparator
	> static void sort
	(
		Pointer pointer,
		std::size_t n,
		Comparator is_before = default_comparator()
	) requires std::is_pointer_v<Pointer>
	{
		sort(pointer, pointer + n, is_before);
	}
};

namespace mak
{
#undef Bidi_It
#undef Bidi_Rn
}
