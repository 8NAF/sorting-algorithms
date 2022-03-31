#pragma once

#include <ranges>

//priv: pointer - range - iterator - view

namespace mak
{
	namespace ranges = std::ranges;

	namespace types
	{
		template <class any>
		struct priv_value;

		template <class iterator_or_range_t>
			requires std::input_iterator<iterator_or_range_t> ||
		std::ranges::range<iterator_or_range_t>
			struct priv_value<iterator_or_range_t>
		{
			using type = std::iter_value_t<iterator_or_range_t>;
		};

		template <std::ranges::viewable_range view_t>
		struct priv_value<view_t>
		{
			using type = std::ranges::range_value_t<view_t>;
		};

		template <class priv_t>
		using priv_value_t = priv_value<priv_t>::type;

		template <class any>
		struct priv_iterator_category;

		template <std::ranges::range range_t>
		struct priv_iterator_category<range_t>
		{
			using type = std::iterator_traits<
				std::ranges::iterator_t<range_t>
			>::iterator_category;
		};

		template <class iterator_or_pointer>
			requires std::input_iterator<iterator_or_pointer>
		struct priv_iterator_category<iterator_or_pointer>
		{
			using type = std::iterator_traits<iterator_or_pointer>::iterator_category;
		};

		template <class priv_t>
		using priv_iterator_category_t = priv_iterator_category<priv_t>::type;
	}
}
