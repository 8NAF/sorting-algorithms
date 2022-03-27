#pragma once

#include "family.hpp"

namespace mak
{
#define	iterator_t forward_iterator_t
#define range_t forward_range_t

	struct bingo_sort;
};

struct mak::bingo_sort : mak::base_sorting_algorithm<
	mak::selection_sort_family
>
{
	template <
		selection_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto is_before_2_way = transform_to_2_way<iterator_t>(is_before);

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
		selection_sort_family_cp::range range_t,
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
