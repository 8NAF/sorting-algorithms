#pragma once

#include <iterator>

namespace mak
{
	namespace adaptors
	{
		template <std::bidirectional_iterator iterator_t>
		class jumping_iterator;
	}
}

template <std::bidirectional_iterator iterator_t>
class mak::adaptors::jumping_iterator
{
private:
	iterator_t iterator;
	std::iter_difference_t<iterator_t> step;

public:
	using iterator_type = iterator_t;
	using difference_type = std::iter_difference_t<iterator_t>;
	using value_type = std::iter_value_t<iterator_t>;
	using reference = std::iter_reference_t<iterator_t>;
	using pointer = std::iterator_traits<iterator_t>::pointer;
	using iterator_category = std::iterator_traits<iterator_t>::iterator_category;

	constexpr jumping_iterator() = default;
	constexpr jumping_iterator
	(
		iterator_type iterator,
		std::iter_difference_t<iterator_type> step
	)
		: iterator{ iterator }
		, step{ step }
	{}

	friend auto operator<=>(jumping_iterator const&, jumping_iterator const&) = default;
	constexpr jumping_iterator& operator=(jumping_iterator const&) = default;

	constexpr operator iterator_type() const {
		return iterator;
	}

	constexpr auto base() const {
		return iterator;
	}

	constexpr auto& operator*() const {
		return *iterator;
	}

	constexpr auto& operator++()
	{
		ranges::advance(iterator, step);
		return *this;
	}

	constexpr auto operator++(int)
	{
		ranges::advance(iterator, step);
		return *this;
	}

	constexpr auto& operator--()
	{
		ranges::advance(iterator, -step);
		return *this;
	}

	constexpr auto operator--(int)
	{
		ranges::advance(iterator, -step);
		return *this;
	}
};
