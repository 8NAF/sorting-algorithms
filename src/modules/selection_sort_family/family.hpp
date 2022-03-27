#pragma once

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "concepts/comparator.concept.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <algorithm>

namespace mak
{
	// for including header file
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;
	using mak::functions::midpoint;
	using mak::functions::transform_to_2_way;

	namespace selection_sort_family_cp
	{
		template <class forward_iterator_t>
		concept iterator = std::forward_iterator<forward_iterator_t>;
		template <class forward_range_t>
		concept range = ranges::forward_range<forward_range_t>;
	}

	template <class T>
	struct selection_sort_family;

	template <>
	struct selection_sort_family<void> {};
}
