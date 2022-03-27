#pragma once

#include "concepts/comparator.concept.hpp"
#include "types/integer.type.hpp"

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <list>
#include <optional>
#include <iostream>

namespace mak
{
#define input_it_t input_iterator_t

	using mak::concepts::iter_two_way_comparator;
	using mak::concepts::iter_comparator;
	using mak::types::generic_break_function;
	using mak::types::default_break_function;
	using mak::types::make_signed_t;
	using mak::types::make_unsigned_t;
	using mak::functions::transform_to_2_way;

	// for including header file
	using mak::types::default_comparator;

	template<
		std::input_iterator input_it_t,
		iter_comparator<input_it_t> comparator_t
	> class bubble_sort_family;
}

template<
	std::input_iterator input_it_t,
	mak::concepts::iter_comparator<input_it_t> comparator_t
>
class mak::bubble_sort_family
{
public:
	using unsigned_opt_t = std::optional<make_unsigned_t<input_it_t>>;

private:

	static inline auto transform_to_2_way =
		transform_to_2_way<input_it_t, comparator_t>;

	std::invoke_result_t<decltype(transform_to_2_way), comparator_t> is_before;
	unsigned_opt_t gap_opt;
	unsigned_opt_t step_opt;

	static auto get_first_not_nullopt
	(
		unsigned_opt_t func,
		unsigned_opt_t cls,
		unsigned_opt_t::value_type default_value
	)
	{
		if (func != std::nullopt) {
			return func.value();
		}
		if (cls != std::nullopt) {
			return cls.value();
		}
		return default_value;
	}

public:

	constexpr bubble_sort_family(
		comparator_t const& is_before,
		unsigned_opt_t gap_opt = std::nullopt,
		unsigned_opt_t step_opt = std::nullopt
	)
		: is_before{ transform_to_2_way(is_before) }
		, gap_opt{ gap_opt }
		, step_opt{ step_opt }
	{ }

	template<
		std::predicate<const input_it_t> break_function_t
	> struct options {
		input_it_t first;
		input_it_t last;
		unsigned_opt_t gap_opt = std::nullopt;
		unsigned_opt_t step_opt = std::nullopt;
		break_function_t is_break_on_first_swap = default_break_function;
	};

	template <
		std::predicate<const input_it_t> break_function_t = generic_break_function<input_it_t>
	> void sort_the_rest(options<break_function_t> options) const
	{
		auto [
			first, last, gap_opt, step_opt, is_break_on_first_swap
		] = options;

		auto gap = get_first_not_nullopt(gap_opt, this->gap_opt, 1);
		auto step = get_first_not_nullopt(step_opt, this->step_opt, gap);

		for (auto current = first; current != last;)
		{
			auto next = ranges::next(current, step);

			auto& current_value = *current;
			auto& next_value = *next;

			if (is_before(next_value, current_value))
			{
				ranges::swap(next_value, current_value);
				if (is_break_on_first_swap(current)) break;
			}

			current = (gap == step) ? next : ranges::next(current, gap);
		}
	}

	auto find_last_swap
	(
		input_it_t first,
		input_it_t last,
		unsigned_opt_t gap_opt = std::nullopt
	) const
	{
		auto gap = get_first_not_nullopt(gap_opt, this->gap_opt, 1);

		auto [current, last_swap] = std::pair(first, first);
		for (decltype(current) next; current != last; current = next)
		{
			next = ranges::next(current, gap);

			auto& current_value = *current;
			auto& next_value = *next;

			if (is_before(next_value, current_value))
			{
				ranges::swap(next_value, current_value);
				last_swap = current;
			}
		}
		return last_swap;
	}

	auto reverse_find_last_swap
	(
		input_it_t first,
		input_it_t last,
		unsigned_opt_t gap_opt = std::nullopt
	) const
		requires std::bidirectional_iterator<input_it_t>
	{
		auto gap = get_first_not_nullopt(gap_opt, this->gap_opt, 1);

		auto [current, last_swap] = std::pair(last, last);
		for (decltype(current) prev; current != first; current = prev)
		{
			prev = ranges::prev(current, gap);

			auto& current_value = *current;
			auto& prev_value = *prev;

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
#undef input_it_t
}
