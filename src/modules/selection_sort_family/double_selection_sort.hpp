#pragma once

#include "family.hpp"

namespace mak
{
#define	iterator_t bidirectional_iterator_t
#define range_t bidirectional_range_t

	namespace double_selection_sort_cp
	{
		template <class iterator_t>
		concept iterator = std::forward_iterator<iterator_t>;
		template <class range_t>
		concept range = ranges::forward_range<range_t>;
	}


	struct double_selection_sort;
	using double_ended_selection_sort = double_selection_sort;
};

struct mak::double_selection_sort : mak::base_sorting_algorithm<
	mak::selection_sort_family
>
{
	template <
		double_selection_sort_cp::iterator iterator_t,
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

		auto middle = midpoint(first, last);
		for (; first != middle; ++first)
		{
			auto [left, right] = ranges::minmax_element(first, last, is_before_2_way);
			if (bool are_all_sorted = (*left == *right); are_all_sorted) return;

			--last;
			right = (first != right) ? right : left;

			ranges::iter_swap(first, left);
			ranges::iter_swap(last, right);
		}
	}

	template <
		double_selection_sort_cp::range range_t,
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
