#pragma once

#include "sorting_algorithm.abstract.hpp"

namespace mak
{
	template<
		std::forward_iterator iterator_t,
		class comparator_t,
		class projection_t
	>
	requires sortable<iterator_t, comparator_t, projection_t>
	class base_family;
}

template<
	std::forward_iterator iterator_t,
	class comparator_t,
	class projection_t
>
requires mak::concepts::sortable<iterator_t, comparator_t, projection_t>
class mak::base_family
{
private:
	static constexpr auto
	transform
	(
		comparator_t comparator,
		projection_t projection
	)
	{
		return [
			comparator = std::move(comparator),
			projection = std::move(projection)
		](auto&& lhs, auto&& rhs) constexpr
		{
			using left_t = decltype(lhs);
			using right_t = decltype(rhs);

			if constexpr (three_way_comparator<comparator_t>) {
				return std::invoke(
					comparator,
					std::invoke(projection, std::forward<left_t>(lhs))
					<=>
					std::invoke(projection, std::forward<right_t>(rhs))
				);
			}
			else {
				return std::invoke(
					comparator,
					std::invoke(projection, std::forward<left_t>(lhs)),
					std::invoke(projection, std::forward<right_t>(rhs))
				);
			}
		};
	}

public:
	std::invoke_result_t<
		decltype(transform), comparator_t, projection_t
	> is_before;

	constexpr base_family(comparator_t comparator, projection_t projection)
		: is_before{ transform(std::move(comparator), std::move(projection)) }
	{}
};
