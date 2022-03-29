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

		// NOTE: std::views::join does not satisfy any range concept (🤬)
		// (std::ranges::range, std::ranges:view, std::ranges::viewable_range, ...)
		// NOTE: std::ranges::iter_value_t does not work, but 
		// std::ranges::iterator_t<>::value_type works (😂)
		template <class value_t>
		struct priv_value<std::ranges::join_view<value_t>>
		{
			using type = std::ranges::iterator_t<
				std::ranges::join_view<value_t>
			>::value_type;
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
			requires std::is_pointer_v<iterator_or_pointer> || std::input_iterator<iterator_or_pointer>
		struct priv_iterator_category<iterator_or_pointer>
		{
			using type = std::iterator_traits<iterator_or_pointer>::iterator_category;
		};

		// NOTE: std::views::join does not satisfy any range concept (🤬)
		// (std::ranges::range, std::ranges:view, std::ranges::viewable_range, ...)
		template <class value_t>
		struct priv_iterator_category<std::ranges::join_view<value_t>>
		{
			using type = std::ranges::iterator_t<
				std::ranges::join_view<value_t>
			>::iterator_category;
		};

		template <class priv_t>
		using priv_iterator_category_t = priv_iterator_category<priv_t>::type;
	}
}

// Hold-on test cases: 
// - std::ranges::owning_view (C++20 | gcc v12)
// - std::ranges::lazy_split_view (C++20 | gcc v12)
// - std::ranges::zip_view (C++23)
// - std::ranges::zip_transform_view (C++23)
// - std::ranges::adjacent_view (C++23)
// - std::ranges::adjacent_transform_view (C++23)
// - std::ranges::join_with_view (C++23)

// Skipping test cases:
// - std::string_view (can not be sorted)
// - std::wstring_view (can not be sorted)
// - std::u8string_view (can not be sorted)
// - std::u16string_view (can not be sorted)
// - std::u32string_view (can not be sorted)
// - std::initializer_list (can not be sorted)
// - std::ranges::basic_istream_view (input_iterator)
// - std::back_insert_iterator (output_iterator)
// - std::front_insert_iterator (output_iterator)
// - std::insert_iterator (output_iterator)

// Successful test cases:
// - std::array
// - std::deque
// - std::forward_list
// - std::list
// - std::string
// - std::wstring
// - std::vector
// - std::span
// - std::valarray
// - std::string
// - std::u8string
// - std::u16string
// - std::u32string
// - pointer
// - array
// - std::views::all
// - std::views::counted
// - std::views::common
// - std::views::drop
// - std::views::drop_while
// - std::views::elements
// - std::views::empty
// - std::views::filter
// - std::views::iota
// - std::views::join
// - std::views::keys
// - std::views::take
// - std::views::transform
// - std::views::take_while
// - std::views::single
// - std::views::split
// - std::views::reverse
// - std::views::values
// - std::ranges::subrange
// - std::ranges::ref_view
// - std::reverse_iterator
// - std::move_iterator
// - std::counted_iterator
// - std::common_iterator
