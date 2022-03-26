#pragma once

// only for including header file
#include "sorting_algorithm.abstract.hpp"
#include "concepts/comparator.concept.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <algorithm>
#include <map>

namespace mak
{
	// for including header file
	using mak::concepts::iter_comparator;
	using mak::types::default_comparator;
	using mak::functions::transform_to_2_way;

	template <class T>
	struct radix_sort_family;

	template <>
	struct radix_sort_family<void> {};
}
