#pragma once

#include "sorting_algorithm.abstract.hpp"

namespace mak
{
	template <class T>
	struct selection_sort_family;

	template <>
	struct selection_sort_family<void> {};
}
