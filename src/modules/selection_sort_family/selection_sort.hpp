#pragma once

#include "family.hpp"

namespace mak
{
#define	Forward_It Forward_Iterator
#define Forward_Rn Forward_Range

	struct selection_sort;
};

struct mak::selection_sort : mak::base_sorting_algorithm<
	mak::selection_sort_family
>
{
	template <
		std::forward_iterator Forward_It,
		iter_comparator<Forward_It> Comparator = default_comparator
	> static void sort
	(
		Forward_It first,
		Forward_It last,
		Comparator is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto is_before_2_way = transform_to_2_way<Forward_It>(is_before);

		while (first != last)
		{
			auto extreme = ranges::min_element(first, last, is_before_2_way);
			ranges::iter_swap(extreme, first);
			++first;
		}
	}

	template <
		ranges::forward_range Forward_Rn,
		iter_comparator<Forward_Rn> Comparator = default_comparator
	> static void sort
	(
		Forward_Rn& range,
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
#undef	Forward_It
#undef Forward_Rn
}

