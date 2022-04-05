#pragma once

#include "types/function.type.hpp"

#include <compare>

namespace mak
{
	using types::default_comparator;
	using types::default_projection;
	
	namespace concepts
	{
		template <class func_t>
		concept three_way_comparator = std::predicate<
			func_t, std::partial_ordering
		>;

		template <
			class iterator_t,
			class comparator_t = default_comparator,
			class projection_t = default_projection
		>
		concept sortable =
		(
			three_way_comparator<comparator_t> ?
			std::sortable<
				iterator_t,
				default_comparator,
				projection_t
			>
			&& std::three_way_comparable<
				std::indirect_result_t<projection_t, iterator_t>
			> :
			std::sortable<iterator_t, comparator_t, projection_t>
		);
	}
}
