#pragma once

#include "concepts/comparator.concept.hpp"
#include "concepts/tag_to_iter.concept.hpp"
#include "types/default.type.hpp"
#include "utils.hpp"

#include <algorithm>

namespace mak
{
	namespace ranges = std::ranges;

	using concepts::iter_comparator;
	using concepts::tag_to_range;
	using concepts::tag_to_iterator;
	using concepts::three_way_comparator;

	using types::default_comparator;
	using types::generic_comparator;
	using types::generic_break_function;
	using types::default_break_function;

	using functions::transform_to_2_way;
	using functions::midpoint;

	template <
		class derived_type,
		template <class...> class family_type,
		std::derived_from<std::input_iterator_tag> tag_t
	> class base_sorting_algorithm;
}

template <
	class injection_t,
	template <class...> class family_type,
	std::derived_from<std::input_iterator_tag> tag_type
>
class mak::base_sorting_algorithm {
protected:

	constexpr base_sorting_algorithm() noexcept = default;

	template <class... arg_ts>
	using family_t = family_type<arg_ts...>;
	using tag_t = tag_type;

	/**
	  * distance(first, last) < 2 => true
	  */
	template <tag_to_iterator<tag_t> iterator_t>
	static constexpr bool no_need_to_sort
	(
		iterator_t first,
		iterator_t last
	)
	{
		if constexpr (std::random_access_iterator<iterator_t>) {
			return ranges::distance(first, last) < 2;
		}

		return (first == last || ++first == last);
	}

public:

	template <
		tag_to_range<tag_t> range_t,
		iter_comparator<range_t> comparator_t = default_comparator
	> static void sort
	(
		range_t& range,
		comparator_t is_before = {}
	)
	{
		injection_t::sort(ranges::begin(range), ranges::end(range), is_before);
	}

	template <
		class pointer_t,
		iter_comparator<pointer_t> comparator_t = default_comparator
	> static void sort
	(
		pointer_t pointer,
		std::size_t n,
		comparator_t is_before = {}
	) requires std::is_pointer_v<pointer_t>
	{
		injection_t::sort(pointer, pointer + n, is_before);
	}
};
