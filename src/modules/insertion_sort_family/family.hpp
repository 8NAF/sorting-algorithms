#pragma once

#include "concepts/comparator.concept.hpp"
#include "types/integer.type.hpp"

// only for including header file
#include "utils.hpp"
#include "types/default.type.hpp"

#include <iterator>
#include <algorithm>
#include <forward_list>
#include <iostream>

namespace mak
{

#define	Forward_It Forward_Iterator
#define	Bidi_It Bidirectional_Iterator

	class insertion_sort_family;

	namespace ranges = std::ranges;

	using mak::concepts::two_way_comparator;

	// for including header file
	using mak::concepts::comparator;
	using mak::types::default_comparator;
	using mak::types::make_unsigned_t;
	using mak::functions::no_need_to_sort;
	using mak::functions::transform_to_2_way;
}

class mak::insertion_sort_family {

private:

	template <std::bidirectional_iterator Bidi_It>
	static void rotate_right
	(
		Bidi_It first,
		Bidi_It last,
		make_unsigned_t<Bidi_It> gap
	)
	{
		auto stored_value = ranges::iter_move(last);
		for (auto current = last; current != first; ) {
			auto temp = ranges::prev(current, gap);
			*current = ranges::iter_move(temp);
			current = temp;
		}
		*first = std::move(stored_value);
	}

protected:

	template <
		std::forward_iterator Forward_It,
		two_way_comparator<std::iter_value_t<Forward_It>> Comparator
	> static auto binary_search
	(
		Forward_It first,
		Forward_It last,
		Comparator is_before,
		make_unsigned_t<Forward_It> gap
	)
	{
		if (gap == 1) {
			return ranges::upper_bound(first, last, *last, is_before);
		}

		// TODO: handle case - gap > 1
		return first;
	}

	template <
		std::bidirectional_iterator Bidi_It,
		two_way_comparator<std::iter_value_t<Bidi_It>> Comparator
	> static auto reverse_linear_search
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before,
		make_unsigned_t<Bidi_It> gap
	)
	{
		auto current = ranges::prev(last, gap);
		while (current != first and is_before(*last, *current)) {
			current = ranges::prev(current, gap);
		}
		return is_before(*last, *current) ? current : ranges::next(current, gap);
	}

	template <
		std::bidirectional_iterator Bidi_It,
		two_way_comparator<std::iter_value_t<Bidi_It>> Comparator,
		std::regular_invocable<Bidi_It, Bidi_It, Comparator, make_unsigned_t<Bidi_It>> Search_Function
	> static void generic_insertion_sort
	(
		Bidi_It first,
		Bidi_It last,
		Comparator is_before,
		make_unsigned_t<Bidi_It> gap,
		Search_Function search
	)
	{
		auto sub_last = ranges::next(first, gap);
		auto sub_first = first;
		auto d_first_sub_last = ranges::distance(first, sub_last);

		while (sub_last != last)
		{
			auto inserted_position = search(sub_first, sub_last, is_before, gap);
			rotate_right(inserted_position, sub_last, gap);

			++sub_last;
			++d_first_sub_last;
			sub_first = (d_first_sub_last % gap == 0) ? first : ranges::next(sub_first);
		}
	}
};

namespace mak
{
#undef Forward_It
#undef Bidi_It
}
