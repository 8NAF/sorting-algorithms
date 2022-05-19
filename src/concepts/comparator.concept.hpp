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
		concept three_way_comparator =
			std::copy_constructible<func_t> &&
			std::predicate<func_t&, std::partial_ordering>;

		template <class func_t, class value_t>
		concept two_way_comparator =
			std::copy_constructible<func_t> &&
			std::predicate<func_t&, value_t&, value_t&>;

		template <class func_t, class value_t>
		concept comparator =
			three_way_comparator<func_t> ||
			two_way_comparator<func_t, value_t>;

		template <
			class iterator_t,
			class comparator_t = default_comparator,
			class projection_t = default_projection
		>
		concept sortable =
		(
			three_way_comparator<comparator_t> ?
			std::sortable<iterator_t, default_comparator, projection_t> &&
			std::three_way_comparable<
				typename std::projected<iterator_t, projection_t>::value_type
			> :
			std::sortable<iterator_t, comparator_t, projection_t>
		);
	}
}
