#pragma once


// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "concepts/comparator.concept.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

namespace mak
{
	// for including header file
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;
	using mak::types::generic_comparator;
	using mak::functions::transform_to_2_way;

	namespace tree_sort_family_cp
	{
		template <class bidirectional_iterator_t>
		concept iterator = std::bidirectional_iterator<bidirectional_iterator_t>;
		template <class bidirectional_range_t>
		concept range = ranges::bidirectional_range<bidirectional_range_t>;
	}

	template <class T>
	class tree_sort_family;

	template <>
	class tree_sort_family<void> {};
}
