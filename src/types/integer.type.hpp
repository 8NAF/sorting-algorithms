#pragma once

#include <ranges>

namespace mak
{
	namespace types
	{
		template <std::input_iterator input_iterator_t>
		using make_unsigned_t = std::make_unsigned_t<std::iter_difference_t<input_iterator_t>>;

		template <std::input_iterator input_iterator_t>
		using make_signed_t = std::make_signed_t<std::iter_difference_t<input_iterator_t>>;
	};
}
