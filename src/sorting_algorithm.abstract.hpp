#pragma once

#include <iterator>

namespace mak
{
#define input_it_t input_iterator_t

	namespace ranges = std::ranges;

	template <template <class...> class Family>
	class base_sorting_algorithm {

	protected:

		constexpr base_sorting_algorithm() noexcept;

		template <class... arg_ts>
		using family_t = Family<arg_ts...>;

		template <std::input_iterator input_it_t>
		static constexpr bool no_need_to_sort
		(
			input_it_t first,
			input_it_t last
		)
		{
			if constexpr (std::random_access_iterator<input_it_t>) {
				return ranges::distance(first, last) < 2;
			}

			return (first == last || ++first == last);
		}
	};

#undef input_it_t
}
