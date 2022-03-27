#pragma once

#include "sorting_algorithm.abstract.hpp"

namespace mak
{
	template <class T>
	struct pancake_sort_family;

	template <>
	struct pancake_sort_family<void> {};
}
