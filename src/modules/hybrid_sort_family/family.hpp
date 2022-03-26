#pragma once

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "concepts/comparator.concept.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <cmath>

namespace mak
{
	// for including header file
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;
	using mak::functions::transform_to_2_way;

	template <class T>
	class hybrid_sort_family;

	template <>
	class hybrid_sort_family<void> { };
}