#pragma once

#include "family.abstract.hpp"

#include <map>

namespace mak
{
	template<class iterator_t, class comparator_t, class projection_t>
	struct radix_sort_family
		: base_family<iterator_t, comparator_t, projection_t>
	{
		using base_family<iterator_t, comparator_t, projection_t>::base_family;
	};
}
