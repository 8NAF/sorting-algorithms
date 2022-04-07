#pragma once

#include "concepts/comparator.concept.hpp"
#include "concepts/tag_to_iter.concept.hpp"
#include "types/function.type.hpp"
#include "utils.hpp"

#include <algorithm>

namespace mak
{
	namespace ranges = std::ranges;

	using concepts::three_way_comparator;
	using concepts::sortable;

	using concepts::tag_to_range;
	using concepts::tag_to_iterator;

	using types::default_comparator;
	using types::default_projection;
	using types::default_break_function;
	using types::default_gap_sequence_function;

	using types::limit;

	using functions::midpoint;

	template <
		class derived_type,
		template <class...> class family_type,
		std::derived_from<std::input_iterator_tag> tag_type
	> class base_sorting_algorithm;
}

template <
	class injection_t,
	template <class...> class family_type,
	std::derived_from<std::input_iterator_tag> tag_type
>
class mak::base_sorting_algorithm
{
public:
	using tag_t = tag_type;

	template <
		tag_to_range<tag_t> range_t,
		class comparator_t = default_comparator,
		class projection_t = default_projection
	>
	requires sortable<ranges::iterator_t<range_t>, comparator_t, projection_t>
	static constexpr void
	sort
	(
		range_t&& range,
		comparator_t is_before = {},
		projection_t projection = {}
	)
	{
		return injection_t::sort(
			ranges::begin(range),
			ranges::end(range),
			std::move(is_before),
			std::move(projection)
		);
	}

protected:
	constexpr base_sorting_algorithm() noexcept = default;

	template <class... arg_ts>
	using family_t = family_type<arg_ts...>;

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
		else {
			return (first == last || ++first == last);
		}
	}
};
