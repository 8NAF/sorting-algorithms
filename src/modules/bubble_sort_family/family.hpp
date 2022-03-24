#pragma once

#include "concepts/comparator.concept.hpp"

// only for including header file
#include "utils.hpp"
#include "types/default.type.hpp"

#include <list>

namespace mak
{
#define Input_It Input_Iterator
#define Bidi_It Bidirectional_Iterator

	class bubble_sort_family;

	namespace ranges = std::ranges;
	using mak::concepts::two_way_comparator;
	using mak::types::generic_break_function;
	using mak::types::default_break_function;

	// for including header file
	using mak::concepts::comparator;
	using mak::types::default_comparator;
	using mak::functions::no_need_to_sort;
	using mak::functions::transform_to_2_way;
}

class mak::bubble_sort_family
{

protected:
	template <std::input_iterator Input_It>
	using make_unsigned_t = std::make_unsigned_t<std::iter_difference_t<Input_It>>;

	template <std::input_iterator Input_It>
	using make_signed_t = std::make_signed_t<std::iter_difference_t<Input_It>>;

	template<
		std::input_iterator Input_It,
		two_way_comparator<std::iter_value_t<Input_It>> Comparator,
		std::predicate<Input_It> Break_Function = generic_break_function<Input_It>
	> struct options {
		Input_It first;
		Input_It last;
		Comparator is_before;
		make_unsigned_t<Input_It> gap = 1;
		make_unsigned_t<Input_It> step = gap;
		Break_Function is_break_on_first_swap = default_break_function;
	};

	template <
		std::input_iterator Input_It,
		two_way_comparator<std::iter_value_t<Input_It>> Comparator,
		std::predicate<Input_It> Break_Function = generic_break_function<Input_It>
	> static void sort_the_rest(options<Input_It, Comparator, Break_Function> options)
	{
		auto [
			first, last, is_before, gap, step, is_break_on_first_swap
		] = options;

		for (auto current = first; current != last; ranges::advance(current, gap))
		{
			auto& current_value = *current;
			auto& next_value = *ranges::next(current, step);

			if (is_before(next_value, current_value))
			{
				ranges::swap(next_value, current_value);
				if (is_break_on_first_swap(current)) break;
			}
		}
	}

	template <
		std::input_iterator Input_It,
		two_way_comparator<std::iter_value_t<Input_It>> Comparator
	> static auto find_last_swap(options<Input_It, Comparator> options)
	{
		[[maybe_unused]] auto [
			first, last, is_before, gap,
				_ignore1, _ignore2
		] = options;

		auto last_swap = first;
		for (auto current = first; current != last; ranges::advance(current, gap))
		{
			auto& current_value = *current;
			auto& next_value = *ranges::next(current, gap);

			if (is_before(next_value, current_value))
			{
				ranges::swap(next_value, current_value);
				last_swap = current;
			}
		}
		return last_swap;
	}

	template <
		std::input_iterator Bidi_It,
		two_way_comparator<std::iter_value_t<Bidi_It>> Comparator
	> static auto reverse_find_last_swap(options<Bidi_It, Comparator> options)
	{
		[[maybe_unused]] auto [
			first, last, is_before, gap,
				_ignore1, _ignore2
		] = options;

		auto last_swap = last;
		for (auto current = last; current != first; ranges::advance(current, -gap))
		{
			auto& current_value = *current;
			auto& prev_value = *ranges::prev(current, gap);

			if (is_before(current_value, prev_value))
			{
				ranges::swap(current_value, prev_value);
				last_swap = current;
			}
		}
		return last_swap;
	}
};

namespace mak
{
#undef Input_It
#undef Bidi_It
}
