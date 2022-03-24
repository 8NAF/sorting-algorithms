#pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <iterator>

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

	static void print_range(std::ranges::input_range auto&& range, auto comparator)
	{
		auto s = std::string();

		for (auto&& value : range)
		{
			//TODO: use std::format
			s += std::to_string(value) + " ";
		}

		s += std::ranges::is_sorted(range, comparator) ? "(is sorted)" : "(is not sorted)";
		std::cout << ((s.length() == 0) ? "<empty>" : s) << std::endl;
	}

	template <class E>
	static void print_range(E* range, auto comparator, size_t n)
	{
		auto s = std::string();
		for (size_t i = 0; i < n; ++i)
		{
			//TODO: use std::format
			s += std::to_string(range[i]) + " ";
		}

		s += std::ranges::is_sorted(range, range + n, comparator) ? "(is sorted)" : "(is not sorted)";
		std::cout << ((s.length() == 0) ? "<empty>" : s) << std::endl;
	}
};

template <class S>
class Tester
{

private:

	template<class Range, class... Nums>
		requires (std::unsigned_integral<Nums>&& ...) && (sizeof...(Nums) <= 1)
	void print_result(Range&& sample, size_t ordinal_number, Nums... nums)
	{
		Printer::print_color<colors::fg_cyan>(
			"\n~~~ sample",
			ordinal_number,
			"~~~"
			);

		std::cout << "\noriginal: ";
		Printer::print_range(sample, std::ranges::equal_to(), nums...);

		S::sort(sample, nums...);
		std::cout << "     asc: ";
		Printer::print_range(sample, std::ranges::less(), nums...);

		S::sort(sample, nums..., std::is_gt);
		std::cout << "    desc: ";
		Printer::print_range(sample, std::ranges::greater(), nums...);
	}

	template <class... Samples>
	void test(std::string name, Samples&&... samples)
	{
		Printer::print_color<colors::fg_yellow>(
			"\n[----------",
			name,
			"----------]\n");

		int index = 0;
		(this->print_result(samples, ++index), ...);
	}

public:

	template <class... Samples>
	void test_std_vector(Samples&&... samples)
	{
		test("std::vector", std::vector(samples)...);
	}

	template <class... Samples>
	void test_std_deque(Samples&&... samples)
	{
		test("std::deque", std::deque(samples)...);
	}

	template <class... Samples>
	void test_std_list(Samples&&... samples)
	{
		test("std::list", std::list(samples)...);
	}

	template <class... Samples>
	void test_std_forward_list(Samples&&... samples)
	{
		test("std::forward_list", std::forward_list(samples)...);
	}

	template <size_t ... N>
	void test_std_array(std::array<int, N>&&... samples)
	{
		test("std::array", samples...);
	}

	template <class... E, std::size_t... N>
	void test_static_array(E(&&...samples)[N])
	{
		test("static array", std::forward<E[N]>(samples)...);
	}

	template <std::size_t ... N, class ...V>
	void test_dynamic_array(V* (&&...samples))
	{
		Printer::print_color<colors::fg_yellow>
			("\n[---------- dynamic array ----------]\n");

		int i = 0;
		(this->print_result(samples, ++i, N), ...);
	}
};
