#pragma once

#include "family.hpp"

namespace mak
{
#define	Forward_It Forward_Iterator
#define Forward_Rn Forward_Range

	class bingo_sort;
};

struct mak::bingo_sort : mak::selection_sort_family
{
	template <
		std::forward_iterator Forward_It,
		comparator<std::iter_value_t<Forward_It>> Comparator = default_comparator
	> static void sort
	(
		Forward_It first,
		Forward_It last,
		Comparator is_before = default_comparator()
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<Forward_It>;
		auto is_before_2_way = transform_to_2_way<value_t>(is_before);

		while (first != last)
		{
			auto extreme = ranges::min_element(first, last, is_before_2_way);
			ranges::iter_swap(extreme, first);
			extreme = first;
			++first;

			ranges::for_each(first, last,
				[&first, &extreme](auto&& value) {
					if (value == *extreme)
					{
						ranges::swap(*first, value);
						++first;
					}
				}
			);
		}
	}

	template <
		ranges::forward_range Forward_Rn,
		comparator<std::iter_value_t<Forward_Rn>> Comparator = default_comparator
	> static void sort
	(
		Forward_Rn& range,
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
#undef	Forward_It
#undef Forward_Rn
}
