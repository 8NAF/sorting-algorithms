#pragma once

#include "modules/bubble_sort_family/bubble_sort.hpp"
#include "test/tester.hpp"

void test_bubble_sort()
{
	auto tester = Tester<mak::bubble_sort>("bubble sort");
	tester.test(
		{ 1 },
		{ -1, -1, -1, -1, -1 },
		{ -1, -2, -3, -4, -5, -6 },
		{ -6, -5, -4, -3, -2, -1 },
		{ 0, 7, -1, 4, 3, 2, 6, 8 },
		{ -1, -3, -9, -8, -8, -1, -2, -6 }
	);
}
