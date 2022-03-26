#pragma once

#include "concepts/comparator.concept.hpp"
#include "types/integer.type.hpp"

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <forward_list>

namespace mak
{
#define	Bidi_It Bidirectional_Iterator

	using mak::functions::transform_to_2_way;
	using mak::types::make_unsigned_t;

	// for including header file
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;

	template<
		std::bidirectional_iterator Bidi_It,
		concepts::iter_comparator<Bidi_It> Comparator
	> class insertion_sort_family;
}

template<
	std::bidirectional_iterator Bidi_It,
	mak::concepts::iter_comparator<Bidi_It> Comparator
>
class mak::insertion_sort_family {

private:

	static inline auto transform_to_2_way =
		transform_to_2_way<Bidi_It, Comparator>;

	std::invoke_result_t<decltype(transform_to_2_way), Comparator> is_before;

	void rotate_right
	(
		Bidi_It first,
		Bidi_It last,
		make_unsigned_t<Bidi_It> gap
	) const
	{
		auto stored_value = ranges::iter_move(last);
		for (auto current = last; current != first; ) {
			auto temp = ranges::prev(current, gap);
			*current = ranges::iter_move(temp);
			current = temp;
		}
		*first = std::move(stored_value);
	}

public:

	insertion_sort_family(Comparator const& is_before)
		: is_before{ transform_to_2_way(is_before) }
	{ }

	template <
		std::invocable<
		Bidi_It, Bidi_It, decltype(is_before), make_unsigned_t<Bidi_It>
		> Search_Function
	> void generic_insertion_sort
	(
		Bidi_It first,
		Bidi_It last,
		make_unsigned_t<Bidi_It> gap,
		Search_Function search
	) const
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

	// requires Forward Iterator
	static auto binary_search
	(
		Bidi_It first,
		Bidi_It last,
		decltype(is_before) is_before,
		make_unsigned_t<Bidi_It> gap
	)
	{
		if (gap == 1) {
			return ranges::upper_bound(first, last, *last, is_before);
		}

		// TODO: handle case - gap > 1
		return first;
	}

	static auto reverse_linear_search
	(
		Bidi_It first,
		Bidi_It last,
		decltype(is_before) is_before,
		make_unsigned_t<Bidi_It> gap
	)
	{
		auto current = ranges::prev(last, gap);
		while (current != first and is_before(*last, *current)) {
			current = ranges::prev(current, gap);
		}
		return is_before(*last, *current) ? current : ranges::next(current, gap);
	}
};

namespace mak
{
#undef Bidi_It
}
