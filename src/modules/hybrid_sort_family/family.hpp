#pragma once

#include "sorting_algorithm.abstract.hpp"

#include <cmath>

namespace mak
{
	template <class T>
	class hybrid_sort_family;

	template <>
	class hybrid_sort_family<void> { };
}
