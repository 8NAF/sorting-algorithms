#pragma once

#include "family.abstract.hpp"
#include "types/integer.type.hpp"

#include <list>
#include <optional>

namespace mak
{
	using types::make_signed_t;
	using types::make_unsigned_t;
	using functions::prev;
	
	template<class iterator_t, class comparator_t, class projection_t>
	class bubble_sort_family;
}

template<class iterator_t, class comparator_t, class projection_t>
class mak::bubble_sort_family
	: private mak::base_family<iterator_t, comparator_t, projection_t>
{
public:
	using unsigned_opt_t = std::optional<make_unsigned_t<iterator_t>>;
	using base_family = base_family<iterator_t, comparator_t, projection_t>;
	using base_family::base_family;

private:
	using forward_iterator_t = iterator_t;
	using bidirectional_iterator_t = iterator_t;

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

	constexpr bubble_sort_family
	(
		comparator_t comparator,
		projection_t projection,
		unsigned_opt_t gap_opt = std::nullopt,
		unsigned_opt_t step_opt = std::nullopt
	)
		: base_family(comparator, projection)
		, gap_opt{ gap_opt }
		, step_opt{ step_opt }
	{ }

	template <class break_function_t = default_break_function<iterator_t>>
	requires std::predicate<break_function_t, const iterator_t>
	struct options
	{
		iterator_t first;
		iterator_t last;
		unsigned_opt_t gap_opt = std::nullopt;
		unsigned_opt_t step_opt = std::nullopt;
		break_function_t is_break_on_first_swap = default_break_function<iterator_t>(
			[](const auto) { return false; }
		);
	};

	template <class break_function_t = default_break_function<iterator_t>>
	requires std::predicate<break_function_t, const forward_iterator_t>
	constexpr void
	sort_the_rest(options<break_function_t> options) const
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

			if (this->is_before(next_value, current_value))
			{
				ranges::swap(next_value, current_value);
				if (is_break_on_first_swap(current)) break;
			}

			current = (gap == step) ? next : ranges::next(current, gap);
		}
	}

	constexpr auto
	find_last_swap
	(
		forward_iterator_t first,
		forward_iterator_t last,
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

			if (this->is_before(next_value, current_value))
			{
				ranges::swap(next_value, current_value);
				last_swap = current;
			}
		}
		return last_swap;
	}

	constexpr auto
	reverse_find_last_swap
	(
		bidirectional_iterator_t first,
		bidirectional_iterator_t last,
		unsigned_opt_t gap_opt = std::nullopt
	) const
		requires std::bidirectional_iterator<bidirectional_iterator_t>
	{
		auto gap = get_first_not_nullopt(gap_opt, this->gap_opt, 1);

		auto [current, last_swap] = std::pair(last, last);
		for (decltype(current) prev; current != first; current = prev)
		{
			prev = ranges::prev(current, gap);

			auto& current_value = *current;
			auto& prev_value = *prev;

			if (this->is_before(current_value, prev_value))
			{
				ranges::swap(current_value, prev_value);
				last_swap = current;
			}
		}
		return last_swap;
	}
};
