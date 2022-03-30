#pragma once

#include <functional>
#include <ranges>
#include <forward_list>

namespace mak
{
	namespace types
	{
		template <class value_t>
		using generic_comparator = std::function<bool(value_t, value_t)>;
		using default_comparator = std::ranges::less;

		template <std::input_iterator input_iterator_t>
		using generic_break_function = std::function<bool(const input_iterator_t)>;
		constexpr auto default_break_function = [](const auto) { return true; };

		using generic_gap_sequence_function = std::function<
			std::forward_list<std::uint64_t>(std::uint64_t)
		>;
	};
}
