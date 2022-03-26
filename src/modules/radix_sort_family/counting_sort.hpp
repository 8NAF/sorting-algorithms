#pragma once

#include "family.hpp"

namespace mak
{
#define Input_It Input_Iterator
#define Input_Rn Input_Range

	struct counting_sort;
};

struct mak::counting_sort : mak::base_sorting_algorithm<
	mak::radix_sort_family
>
{
	template <
		std::input_iterator Input_It,
		iter_comparator<Input_It> Comparator = default_comparator
	> static void sort
	(
		Input_It first,
		Input_It last,
		Comparator is_before = {}
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<Input_It>;
		using comparator_t = generic_comparator<value_t>;

		auto is_before_2_way = transform_to_2_way<Input_It>(is_before);
		std::multimap<value_t, value_t, comparator_t> keys_values(is_before_2_way);

		ranges::for_each(first, last,
			[&keys_values](auto const& key) {
				keys_values.emplace(key, std::move(key));
			}
		);

		for (auto& [key, value] : keys_values) {
			*(first++) = value;
		}
	}

	template <
		ranges::input_range Input_Rn,
		iter_comparator<Input_Rn> Comparator = default_comparator
	> static void sort
	(
		Input_Rn& range,
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
#undef Input_It
#undef Input_Rn
}
