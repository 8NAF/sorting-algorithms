#pragma once

#include <iostream>
#include <algorithm>
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
		return ((std::cout << open << args << ' ' << close), ...);
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

	template<class Range, class... Number>
		requires (std::unsigned_integral<Number> && ...) && (sizeof...(Number) <= 1)
	void execute_all_test_cases
	(
		std::string const& range_name,
		Range& sample,
		Number... n
	)
	{
		auto make_view = [&n...](auto& target) -> decltype(auto) {
			if constexpr (sizeof...(Number) == 1) return std::span{ target, n... };
			else if constexpr (std::is_array_v<Range>) return std::span{ target, std::size(target) };
			else return target;
		};
		auto copy = [&n...](auto& src, auto& des) {
			if constexpr (sizeof...(Number) == 1) ranges::copy(std::span{ src, n... }, des);
			else if constexpr (std::is_array_v<Range>) ranges::copy(src, des);
			else des = src;
		};
		auto begin = [](auto& range) {
			if constexpr (sizeof...(Number) == 1) return range;
			else return ranges::begin(range);
		};
		auto end = [&n...](auto& range) {
			if constexpr (sizeof...(Number) == 1) return range + (... + n);
			else return ranges::end(range);
		};

		using value_t = std::iter_value_t<decltype(sample)>;

		std::remove_reference_t<decltype(sample)> cloner;
		if constexpr (sizeof...(Number) == 1) {
			cloner = std::make_unique<value_t[]>(n...).release();
		}

		std::map<value_t, std::size_t> original_stored_number;
		for (auto&& value : make_view(sample)) {
			++original_stored_number[value];
		}

		auto check_passed = [&](auto&& comparator_name, auto&& comparator)
		{
			auto cloner_view = make_view(cloner);
			auto is_passed = Tester::is_passed(original_stored_number, cloner_view, comparator);
			if (!is_passed) {
				Printer::print_color<
					colors::fg_red
					// TODO: use std::format
				>("TC<" + range_name + ", range, " + comparator_name + "> : failed\n");
				Printer::print_range(cloner_view);
				this->is_all_passed = false;
			}
		};

		auto test_range = [&]<typename two_way_comparator_t, typename... comparator_t>(
			auto const& comparator_name,
			two_way_comparator_t two_way_comparator,
			comparator_t... comparator
			)
		{
			copy(sample, cloner);
			S::sort(cloner, n..., comparator...);
			check_passed(comparator_name, two_way_comparator);
		};

		auto test_iterator = [&]<typename two_way_comparator_t, typename... comparator_t>(
			auto const& comparator_name,
			two_way_comparator_t two_way_comparator,
			comparator_t... comparator
			)
		{
			copy(sample, cloner);
			S::sort(begin(cloner), end(cloner), comparator...);
			check_passed(comparator_name, two_way_comparator);
		};

		test_range("null", ranges::less());
		test_range("std::less()", std::less<value_t>(), std::less<value_t>());
		test_range("std::greater()", std::greater<value_t>(), std::greater<value_t>());
		test_range("ranges::less()", ranges::less(), ranges::less());
		test_range("ranges::greater()", ranges::greater(), ranges::greater());
		test_range("std::is_lt", ranges::less(), std::is_lt);
		test_range("std::is_gt", ranges::greater(), std::is_gt);

		test_iterator("null", ranges::less());
		test_iterator("std::less()", std::less<value_t>(), std::less<value_t>());
		test_iterator("std::greater()", std::greater<value_t>(), std::greater<value_t>());
		test_iterator("ranges::less()", ranges::less(), ranges::less());
		test_iterator("ranges::greater()", ranges::greater(), ranges::greater());
		test_iterator("std::is_lt", ranges::less(), std::is_lt);
		test_iterator("std::is_gt", ranges::greater(), std::is_gt);
	}

	template <class E, std::size_t N>
	void test_sample(E(&sample)[N], std::size_t i)
	{
		Printer::print_color<colors::fg_cyan>("\nsample", i, ":");
		Printer::print_range(sample);

		is_all_passed = true;

		auto v = std::vector(ranges::begin(sample), ranges::end(sample));
		auto d = std::deque(ranges::begin(sample), ranges::end(sample));
		auto l = std::list(ranges::begin(sample), ranges::end(sample));
		auto s = std::string(ranges::begin(sample), ranges::end(sample));
		auto a = std::to_array(sample);

		execute_all_test_cases("std::vector", v);
		execute_all_test_cases("std::deque", d);
		execute_all_test_cases("std::list", l);
		execute_all_test_cases("std::array", a);
		execute_all_test_cases("std::string", s);
		execute_all_test_cases("static array", sample);

		if constexpr (std::is_same_v<typename S::tag_t, std::forward_iterator_tag>) {
			auto f = std::forward_list(ranges::begin(sample), ranges::end(sample));
			execute_all_test_cases("std::forward_list", f);
		}

		auto p = new E[N];
		ranges::copy(sample, p);
		execute_all_test_cases("dynamic array", p, N);
		delete[] p;

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
		Printer::print_color<colors::fg_blue>("\n[##########", sorting_name, "##########]\n");

		int i = 0;
		(test_sample(samples, ++i), ...);

		Printer::print_color<
			colors::fg_blue
		>("\n[" + std::string(sorting_name.length() + (10 + 1) * 2, '#') + "]\n");
	}
};
