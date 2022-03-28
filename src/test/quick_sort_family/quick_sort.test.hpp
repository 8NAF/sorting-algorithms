#pragma once

#include "modules/quick_sort_family/quick_sort.hpp"
#include "test/tester.hpp"

void test_quick_sort()
{
	auto tester = Tester<mak::quick_sort>("quick sort");
	tester.test(
		{ 1 },
		{ 9, 9, 9, 9, 9 },
		{ -1, -2, -3, -4, -5, -6 },
		{ -6, -5, -4, -3, -2, -1 },
		{ 6, 1, 9, 0, 1, 3, 5, 7, 7, 1, 3, 9 },
		{ -1, -3, -9, -1, -6, -5, -5, -3, -4 }
	);
}
