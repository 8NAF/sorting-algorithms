#pragma once

#include "sorting_algorithm.abstract.hpp"

namespace mak
{
	template <class T>
	struct cycle_sort_family;
	template <>
	struct cycle_sort_family<void> { };
}
