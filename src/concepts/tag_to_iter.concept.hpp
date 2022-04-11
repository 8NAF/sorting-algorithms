#pragma once

#include <ranges>

namespace mak
{
	namespace concepts
	{
		/**
		 * Check the corresponding range concept based on the tag provided
		 */
		template <class range_t, class tag_t>
		concept tag_to_range =
			std::derived_from<tag_t, std::input_iterator_tag> &&
			(
				std::same_as<tag_t, std::contiguous_iterator_tag> ? std::ranges::contiguous_range<range_t> :
				std::same_as<tag_t, std::random_access_iterator_tag > ? std::ranges::random_access_range<range_t> :
				std::same_as<tag_t, std::bidirectional_iterator_tag> ? std::ranges::bidirectional_range<range_t> :
				std::same_as<tag_t, std::forward_iterator_tag> ? std::ranges::forward_range<range_t> :
				std::ranges::input_range<range_t>
			);

		/**
		  * Check the corresponding iterator concept based on the tag provided
		  */
		template <class iterator_t, class tag_t>
		concept tag_to_iterator =
			std::derived_from<tag_t, std::input_iterator_tag> &&
			(
				std::same_as<tag_t, std::contiguous_iterator_tag> ? std::contiguous_iterator<iterator_t> :
				std::same_as<tag_t, std::random_access_iterator_tag > ? std::random_access_iterator<iterator_t> :
				std::same_as<tag_t, std::bidirectional_iterator_tag> ? std::bidirectional_iterator<iterator_t> :
				std::same_as<tag_t, std::forward_iterator_tag> ? std::forward_iterator<iterator_t> :
				std::input_iterator<iterator_t>
			);
	}
}
