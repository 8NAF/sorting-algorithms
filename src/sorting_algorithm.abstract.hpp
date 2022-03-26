#pragma once

#include <iterator>

namespace mak
{
#define Input_It Input_Iterator

	namespace ranges = std::ranges;

	template <template <class...> class Family>
	class base_sorting_algorithm {

	protected:

		constexpr base_sorting_algorithm() noexcept;

		template <class... Args>
		using family_t = Family<Args...>;

		template <std::input_iterator Input_It>
		static constexpr bool no_need_to_sort
		(
			Input_It first,
			Input_It last
		)
		{
			if constexpr (std::random_access_iterator<Input_It>) {
				return ranges::distance(first, last) < 2;
			}

			return (first == last || ++first == last);
		}
	};

#undef Input_It
}
