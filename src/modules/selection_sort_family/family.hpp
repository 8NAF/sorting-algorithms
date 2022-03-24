#pragma once

// only for including header file
#include "concepts/comparator.concept.hpp"
#include "utils.hpp"
#include "types/default.type.hpp"

#include <algorithm>

namespace mak
{

	struct selection_sort_family {};

	// for including header file
	namespace ranges = std::ranges;

	using mak::concepts::comparator;
	using mak::types::default_comparator;
	using mak::functions::midpoint;
	using mak::functions::no_need_to_sort;
	using mak::functions::transform_to_2_way;
}
