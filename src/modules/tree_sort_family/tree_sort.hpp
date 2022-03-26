#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	struct tree_sort;
	using BST_sort = tree_sort;
};

struct mak::tree_sort : mak::base_sorting_algorithm<
	mak::tree_sort_family
>
{
	template <
		std::bidirectional_iterator Bidi_It,
		iter_comparator<Bidi_It> Comparator = default_comparator
	> static void sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<Bidi_It>;
		using comparator_t = generic_comparator<value_t>;

		auto is_before_2_way = transform_to_2_way<Bidi_It>(is_before);
		BST <value_t, comparator_t> tree;

		ranges::for_each(first, last,
			[&tree](auto& value) {
				tree.emplace(std::move(value));
			}
		);

		tree.LNR(
			[&first](auto const& value) mutable {
				*first = value;
				++first;
			}
		);
	}

	template <
		ranges::bidirectional_range Bidi_Rn,
		iter_comparator<Bidi_Rn> Comparator = default_comparator
	> static void sort
	(
		Bidi_Rn& range,
		Comparator is_before = {}
	)
	{
		sort(ranges::begin(range), ranges::end(range), is_before);
	}

	template <
		class Pointer,
		iter_comparator<Pointer> Comparator = default_comparator
	> static void sort
	(
		Pointer pointer,
		std::size_t n,
		Comparator is_before = {}
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
