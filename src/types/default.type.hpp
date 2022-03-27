#pragma once

#include <functional>
#include <ranges>

namespace mak
{
#define input_it_t input_iterator_t

	namespace types
	{
		using default_comparator = std::ranges::less;

		template <class value_t>
		using generic_comparator = std::function<bool(value_t, value_t)>;

		template <std::input_iterator input_it_t>
		using generic_break_function = std::function<bool(const input_it_t)>;

		constexpr auto default_break_function = [](const auto) { return true; };
	};

#undef input_it_t
}
