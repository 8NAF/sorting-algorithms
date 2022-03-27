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
#define iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	struct heap_sort;
};

struct mak::heap_sort : mak::base_sorting_algorithm<
	mak::heap_sort_family
>
{
	template <
		heap_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<iterator_t, comparator_t>(is_before);

		family.make_heap(first, last);
		family.do_sort(first, last);
	}

	template <
		heap_sort_family_cp::range range_t,
		iter_comparator<range_t> comparator_t = default_comparator
	> static void sort
	(
		range_t& range,
		comparator_t is_before = {}
	)
	{
		sort(ranges::begin(range), ranges::end(range), is_before);
	}

	template <
		class pointer_t,
		iter_comparator<pointer_t> comparator_t = default_comparator
	> static void sort
	(
		pointer_t pointer,
		std::size_t n,
		comparator_t is_before = {}
	) requires std::is_pointer_v<pointer_t>
	{
		sort(pointer, pointer + n, is_before);
	}
};

namespace mak
{
#undef iterator_t
#undef range_t
}
