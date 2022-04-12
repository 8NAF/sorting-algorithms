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
protected:
	comparator_t comparator;
	projection_t projection;

private:
	constexpr static auto
	make_before_proj(comparator_t& comparator, projection_t& projection)
	{
		return [&]<class left_t, class right_t>
		(left_t&& lhs, right_t&& rhs) constexpr
		{
			if constexpr (three_way_comparator<comparator_t>) {
				return std::invoke(comparator,
					std::invoke(projection, std::forward<left_t>(lhs)) <=>
					std::invoke(projection, std::forward<right_t>(rhs))
				);
			}
			else {
				return std::invoke(comparator,
					std::invoke(projection, std::forward<left_t>(lhs)),
					std::invoke(projection, std::forward<right_t>(rhs))
				);
			}
		};
	}

	constexpr static auto
	make_equal_proj(projection_t& projection)
	{
		return [&]<class left_t, class right_t>
		(left_t&& lhs, right_t&& rhs) constexpr
		{
			return ranges::equal_to()(
				std::invoke(projection, std::forward<left_t>(lhs)),
				std::invoke(projection, std::forward<right_t>(rhs))
			);
		};
	}

public:
	std::invoke_result_t<
		decltype(make_before_proj), comparator_t&, projection_t&
	> is_before;

	std::invoke_result_t<
		decltype(make_equal_proj), projection_t&
	> is_equal;

	constexpr base_family(comparator_t $comparator, projection_t $projection)
		: comparator{ std::move($comparator) }
		, projection{ std::move($projection) }
		, is_before{ make_before_proj(comparator, projection) }
		, is_equal{make_equal_proj(projection)}
	{}
};
