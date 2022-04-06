#pragma once

#include <iostream>
#include <algorithm>
#include <memory_resource>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <iterator>
#include <span>
#include <map>
#include <memory>
#include <string_view>
#include <ranges>

namespace ranges = std::ranges;
namespace views = std::views;

enum colors
{
	fg_black = 30,
	fg_red = 31,
	fg_green = 32,
	fg_yellow = 33,
	fg_blue = 34,
	fg_magenta = 35,
	fg_cyan = 36,
	fg_white = 37,

	bg_black = 40,
	bg_red = 41,
	bg_green = 42,
	bg_yellow = 43,
	bg_blue = 44,
	bg_magenta = 45,
	bg_cyan = 46,
	bg_white = 47,
};

struct Printer
{
	template <size_t color, class... Args>
	static decltype(auto) print_color(Args&&... args)
	{
		//TODO: use std::format
		auto open = "\033[1;" + std::to_string(color) + "m";
		decltype(open) close = "\033[0m";
		return ((std::cout << open << args << close), ...);
	}

	static void print_range(ranges::input_range auto&& range)
	{
		auto s = std::string();

		for (auto&& value : range)
		{
			//TODO: use std::format
			s += std::to_string(value) + " ";
		}

		std::cout << ((s.length() == 0) ? "<empty>" : s) << std::endl;
	}
};

template <class S>
class Tester
{
private:
	static auto is_passed(auto&& original_stored_number, auto&& actual, auto&& comparator)
	{
		std::remove_reference_t<decltype(original_stored_number)> actual_stored_number;
		for (auto&& value : actual) {
			++actual_stored_number[value];
		}
		return original_stored_number == actual_stored_number &&
			ranges::is_sorted(actual, comparator);
	}

	template<class Range>
	void execute_all_test_cases
	(
		std::string_view range_name,
		Range& sample
	)
	{
		auto copy = [](auto& src, auto& des)
		{
			if constexpr (std::is_array_v<Range>) ranges::copy(src, des);
			else des = src;
		};

		std::remove_reference_t<decltype(sample)> cloner;

		using value_t = std::ranges::range_value_t<decltype(sample)>;
		std::map<value_t, std::size_t> original_stored_number;
		for (auto&& value : sample) {
			++original_stored_number[value];
		}

		auto check_passed = [&](auto&& comparator_name, auto&& overloaded_name, auto&& comparator)
		{
			auto is_passed = Tester::is_passed(original_stored_number, cloner, comparator);
			if (!is_passed) {
				Printer::print_color<
					colors::fg_red
					// TODO: use std::format
				>("TC< ", range_name, ", ", comparator_name, ", ", overloaded_name, " > : failed\n");
				Printer::print_range(cloner);
				this->is_all_passed = false;
			}
		};

		auto test_impl = [&]<typename two_way_comparator_t, typename... comparator_t>
		(
			auto const& comparator_name,
			two_way_comparator_t two_way_comparator,
			comparator_t... comparator
		)
		{
			copy(sample, cloner);
			S::sort(cloner, comparator...);
			check_passed(comparator_name, "range", two_way_comparator);

			copy(sample, cloner);
			S::sort(ranges::begin(cloner), ranges::end(cloner), comparator...);
			check_passed(comparator_name, "iterator", two_way_comparator);
		};

		auto test_cases = std::tuple
		(
			std::tuple("null", ranges::less()),
			std::tuple("std::less()", std::less<value_t>(), std::less<value_t>()),
			std::tuple("std::greater()", std::greater<value_t>(), std::greater<value_t>()),
			std::tuple("ranges::less()", ranges::less(), ranges::less()),
			std::tuple("ranges::greater()", ranges::greater(), ranges::greater()),
			std::tuple("std::is_lt", ranges::less(), std::is_lt),
			std::tuple("std::is_gt", ranges::greater(), std::is_gt)
		);

		[&]<std::size_t... index_t>(std::index_sequence<index_t...>)
		{
			(std::apply(test_impl, std::get<index_t>(test_cases)), ...);
		}(std::make_index_sequence<std::tuple_size_v<decltype(test_cases)>>{});
	}

	template <class E, std::size_t N>
	void test_sample(E(&sample)[N], std::size_t i)
	{
		Printer::print_color<colors::fg_cyan>("\nsample ", i, ": ");
		Printer::print_range(sample);

		is_all_passed = true;

		auto p = new E[N];
		ranges::copy(sample, p);

		auto all_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto counted_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto common_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto drop_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto drop_while_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto ref_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto reverse_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto take_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		//auto take_while_vr = std::vector(ranges::begin(sample), ranges::end(sample));
		auto subrange_r = std::vector(ranges::begin(sample), ranges::end(sample));

		std::vector<std::pair<int, E>> elements_vr(std::ranges::size(sample));
		std::vector<std::pair<int, E>> keys_vr(std::ranges::size(sample));
		std::vector<std::pair<int, E>> values_vr(std::ranges::size(sample));

		std::ranges::for_each(sample, [&elements_vr, i = 0](auto&& value) mutable {
			elements_vr[i++] = std::pair(std::rand(), value);
		});
		std::ranges::for_each(sample, [&keys_vr, i = 0](auto&& value) mutable {
			keys_vr[i++] = std::pair(std::rand(), value);
		});
		std::ranges::for_each(sample, [&values_vr, i = 0](auto&& value) mutable {
			values_vr[i++] = std::pair(std::rand(), value);
		});

		auto test_cases = std::tuple(
			std::tuple("std::vector", std::vector(ranges::begin(sample), ranges::end(sample))),
			std::tuple("std::deque", std::deque(ranges::begin(sample), ranges::end(sample))),
			std::tuple("std::list", std::list(ranges::begin(sample), ranges::end(sample))),
			std::tuple("std::string", std::string(ranges::begin(sample), ranges::end(sample))),

			std::tuple("std::pmr::vector", std::pmr::vector<E>(ranges::begin(sample), ranges::end(sample))),
			std::tuple("std::pmr::deque", std::pmr::deque<E>(ranges::begin(sample), ranges::end(sample))),
			std::tuple("std::pmr::list", std::pmr::list<E>(ranges::begin(sample), ranges::end(sample))),
			std::tuple("std::pmr::string", std::pmr::string(ranges::begin(sample), ranges::end(sample))),

			std::tuple("std::span", std::span{ p, N }),
			std::tuple("std::array", std::to_array(sample)),

			std::tuple("std::views::all_t", views::all(all_vr)),
			std::tuple("std::views::counted", views::counted(counted_vr.begin(), ranges::size(counted_vr))),
			std::tuple("std::views::common_view", views::common(common_vr)),
			std::tuple("std::ranges::drop_view", drop_vr | views::drop(0)),
			std::tuple("std::ranges::drop_while_view", drop_while_vr | views::drop_while([](auto&&) { return false; })),
			std::tuple("std::ranges::empty_view", views::empty<E>),
			std::tuple("std::ranges::ref_view", ranges::ref_view(ref_vr)),
			std::tuple("std::ranges::reverse_view", reverse_vr | views::reverse),
			std::tuple("std::ranges::single_view", views::single(E{})),
			std::tuple("std::ranges::take_view", take_vr | views::take(ranges::size(take_vr))),
			//std::tuple("std::ranges::take_while_view", take_while_vr | views::take_while([](auto&&) { return true; })),
			std::tuple("std::ranges::subrange", ranges::subrange(subrange_r.begin(), subrange_r.end()))
		);

		[this, &test_cases] <std::size_t... index_t>(std::index_sequence<index_t...>)
		{
			(this->execute_all_test_cases(
				std::get<0>(std::get<index_t>(test_cases)),
				std::get<1>(std::get<index_t>(test_cases))
			), ...);
		}(std::make_index_sequence<std::tuple_size_v<decltype(test_cases)>>{});

		// static array can not be a return type
		execute_all_test_cases("static array", sample);

		if constexpr (std::is_same_v<typename S::tag_t, std::forward_iterator_tag>)
		{
			auto f = std::forward_list(ranges::begin(sample), ranges::end(sample));
			auto pf = std::pmr::forward_list<E>(ranges::begin(sample), ranges::end(sample));

			execute_all_test_cases("std::forward_list", f);
			execute_all_test_cases("std::pmr::forward_list", pf);
		}

		if (is_all_passed) {
			Printer::print_color<colors::fg_green>("Pass all test cases.")
				<< std::endl;
		}
	}

	std::string sorting_name;
	bool is_all_passed;

public:
	Tester(std::string const& sorting_name)
		: sorting_name{ sorting_name }
	{
		ranges::transform(
			this->sorting_name,
			this->sorting_name.begin(),
			[](auto&& v) { return std::toupper(v); }
		);
	}

	template <class... E, std::size_t... N>
	void test(E(&&...samples)[N])
	{
		Printer::print_color<colors::fg_blue>("\n[########## ", sorting_name, " ##########]\n");

		int i = 0;
		(test_sample(samples, ++i), ...);

		Printer::print_color<
			colors::fg_blue
		>("\n[", std::string(sorting_name.length() + (10 + 1) * 2, '#'), "]\n");
	}
};
