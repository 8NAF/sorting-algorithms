#pragma once

#include <functional>
#include <ranges>

namespace mak

{
	namespace types
	{
		using default_comparator = std::ranges::less;

		template <std::input_iterator It>
		using default_break_function = std::function<bool(It)>;
	};
}
