#pragma once

#include <functional>
#include <ranges>

namespace mak
{
#define Input_It Input_Iterator

	namespace types
	{
		using default_comparator = std::ranges::less;

		template <class Value>
		using generic_comparator = std::function<bool(Value, Value)>;

		template <std::input_iterator Input_It>
		using generic_break_function = std::function<bool(Input_It)>;

		constexpr auto default_break_function = [](auto) { return true; };
	};

#undef Input_It
}
