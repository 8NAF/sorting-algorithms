#pragma once

#include <iterator>
#include <compare>

namespace mak
{
	namespace concepts
	{
		template <class func_t>
		concept three_way_comparator = std::predicate<
			func_t,
			std::partial_ordering
		>;

		template <class func_t, class val_t>
		concept two_way_comparator = std::predicate<func_t, val_t, val_t>;

		template <class func_t, class iter_t>
		concept iter_two_way_comparator =
			(std::input_iterator<iter_t> || std::ranges::range<iter_t>) &&
			two_way_comparator<func_t, std::iter_value_t<iter_t>>;

		template <class func_t, class val_t>
		concept comparator = three_way_comparator<func_t> ||
			two_way_comparator<func_t, val_t>;

		template <class func_t, class iter_t>
		concept iter_comparator = three_way_comparator<func_t> ||
			iter_two_way_comparator<func_t, iter_t>;
	}
}
