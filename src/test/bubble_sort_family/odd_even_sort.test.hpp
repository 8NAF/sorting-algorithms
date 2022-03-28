#pragma once

#include "modules/bubble_sort_family/odd_even_sort.hpp"
#include "test/tester.hpp"

void test_odd_even_sort()
{
	auto tester = Tester<mak::odd_even_sort>("odd even sort");
	tester.test(
		{ 1 },
		{ -4, -4, -4, -4, -4 },
		{ -1, -2, -3, -4, -5, -6 },
		{ -6, -5, -4, -3, -2, -1 },
		{ 5, 1, 7, 8, 2, 0 },
		{ -1, -3, -1, -8, -8, -5, -7, -6, -9 }
	);
}
