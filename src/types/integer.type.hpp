#pragma once

#include <ranges>

namespace mak
{
#define Input_It Input_Iterator

	namespace types
	{
		template <std::input_iterator Input_It>
		using make_unsigned_t = std::make_unsigned_t<std::iter_difference_t<Input_It>>;

		template <std::input_iterator Input_It>
		using make_signed_t = std::make_signed_t<std::iter_difference_t<Input_It>>;
	};

#undef Input_It
}
