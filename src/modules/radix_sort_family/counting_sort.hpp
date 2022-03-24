#pragma once

#include "family.hpp"

namespace mak
{
#define Bidi_It Bidirectional_Iterator
#define Bidi_Rn Bidirectional_Range

	class counting_sort;
};

struct mak::counting_sort : mak::radix_sort_family
{
	template <
		std::input_or_output_iterator Bidi_It,
		comparator<std::iter_value_t<Bidi_It>> Comparator = default_comparator
	> static void sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before = default_comparator()
	)
	{
		if (no_need_to_sort(first, last)) return;

		using value_t = std::iter_value_t<Bidi_It>;
		using comparator_t = std::invoke_result_t<
			decltype(transform_to_2_way<value_t, Comparator>),
			Comparator
		>;

		auto is_before_2_way = transform_to_2_way<value_t>(is_before);
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
		ranges::range Bidi_Rn,
		comparator<std::iter_value_t<Bidi_Rn>> Comparator = default_comparator
	> static void sort
	(
		Bidi_Rn& range,
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
#undef Bidi_It
#undef Bidi_Rn
}
