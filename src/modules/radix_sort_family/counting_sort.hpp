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
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<forward_iterator_t, comparator_t, projection_t>
	static constexpr void
	sort
	(
		forward_iterator_t first,
		forward_iterator_t last,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		auto family = family_t<
			forward_iterator_t, comparator_t, projection_t
		>(std::move(is_before), std::move(projection));

		using value_t = std::iter_value_t<forward_iterator_t>;
		std::multimap<
			value_t, value_t, decltype(family.is_before)
		> keys_values(family.is_before);

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
