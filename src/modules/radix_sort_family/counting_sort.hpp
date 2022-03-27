#pragma once

#include "family.hpp"

namespace mak
{
#define iterator_t forward_iterator_t
#define range_t forward_range_t

	struct counting_sort;
};

struct mak::counting_sort : mak::base_sorting_algorithm<
	mak::radix_sort_family
>
{
	template <
		radix_sort_family_cp::iterator iterator_t,
		iter_comparator<iterator_t> comparator_t = default_comparator
	> static void sort
	(
		iterator_t first,
		iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<iterator_t>;
		using two_way_comparator_t = generic_comparator<value_t>;

		auto is_before_2_way = transform_to_2_way<iterator_t>(is_before);
		std::multimap<
			value_t, value_t, two_way_comparator_t
		> keys_values(is_before_2_way);

		ranges::for_each(first, last,
			[&keys_values](auto& key) {
				keys_values.emplace(key, std::move(key));
			}
		);

		for (auto& [key, value] : keys_values) {
			*(first++) = value;
		}
	}

	template <
		radix_sort_family_cp::range range_t,
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
