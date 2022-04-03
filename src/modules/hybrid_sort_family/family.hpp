#pragma once

#include "family.abstract.hpp"

#include <cmath>

namespace mak
{
	template<class iterator_t, class comparator_t, class projection_t>
	struct hybrid_sort_family
		: base_family<iterator_t, comparator_t, projection_t>
	{
		using base_family<iterator_t, comparator_t, projection_t>::base_family;
	};
}
