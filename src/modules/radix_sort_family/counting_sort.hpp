#pragma once

#include "family.hpp"

namespace mak
{
	struct counting_sort;
}

struct mak::counting_sort : mak::base_sorting_algorithm<
	mak::counting_sort,
	mak::radix_sort_family,
	std::forward_iterator_tag
>
{
	using base_sorting_algorithm::sort;

	template <
		tag_to_iterator<tag_t> forward_iterator_t,
		iter_comparator<forward_iterator_t> comparator_t = default_comparator
	> static void sort
	(
		forward_iterator_t first,
		forward_iterator_t last,
		comparator_t is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<forward_iterator_t>;
		using two_way_comparator_t = generic_comparator<value_t>;

		auto is_before_2_way = transform_to_2_way<forward_iterator_t>(is_before);
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
};
