#pragma once

#include "sorting_algorithm.abstract.hpp"

#include <map>

namespace mak
{
	template <class T>
	struct radix_sort_family;

	template <>
	struct radix_sort_family<void> {};
}
