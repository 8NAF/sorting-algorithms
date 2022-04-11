#pragma once

#include <iterator>

namespace mak
{
	namespace ranges = std::ranges;

	namespace adaptors
	{
		template <
			std::forward_iterator iterator_t,
			std::sentinel_for<iterator_t> sentinel_t
		>
		class cyclic_iterator;
	}
}

template <
	std::forward_iterator iterator_t,
	std::sentinel_for<iterator_t> sentinel_t
>
class mak::adaptors::cyclic_iterator
{
private:
	iterator_t current;
	iterator_t first;
	sentinel_t last;

public:
	using sentinel_type = sentinel_t;
	using iterator_type = iterator_t;
	using difference_type = std::iter_difference_t<iterator_t>;
	using value_type = std::iter_value_t<iterator_t>;
	using reference = std::iter_reference_t<iterator_t>;
	using pointer = std::iterator_traits<iterator_t>::pointer;
	using iterator_category = std::iterator_traits<iterator_t>::iterator_category;

	constexpr cyclic_iterator() = default;
	constexpr cyclic_iterator
	(
		iterator_type first,
		sentinel_type last
	)
		: first{ first }
		, last{ last }
		, current{ first }
	{}

	constexpr auto const& current_position() const {
		return current;
	}

	constexpr cyclic_iterator
	(
		iterator_type first,
		sentinel_type last,
		iterator_type current
	)
		: first{ first }
		, last{ last }
		, current{ current }
	{}

	constexpr friend auto operator==(cyclic_iterator const& a, cyclic_iterator const& b) {
		return a.current == b.current;
	}

	constexpr cyclic_iterator& operator=(cyclic_iterator const&) = default;

	constexpr operator iterator_type() const {
		return current;
	}

	constexpr auto base() const {
		return current;
	}

	constexpr auto& operator*() const {
		return *current;
	}

	constexpr auto& operator++()
	{
		current = (current == last) ? first : ranges::next(current);
		return *this;
	}

	constexpr auto operator++(int)
	{
		current = (current == last) ? first : ranges::next(current);
		return *this;
	}

	constexpr bool is_not_last() {
		return current != last;
	}
};
