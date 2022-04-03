#pragma once

#include <functional>
#include <ranges>
#include <forward_list>

namespace mak
{
	namespace types
	{
		template <std::input_iterator iterator_t>
		using default_break_function = std::function<bool(const iterator_t)>;
		using default_comparator = std::ranges::less;
		using default_projection = std::identity;
		using default_gap_sequence_function = std::function<
			std::forward_list<std::uint64_t>(std::uint64_t)
		>;
	};
}
