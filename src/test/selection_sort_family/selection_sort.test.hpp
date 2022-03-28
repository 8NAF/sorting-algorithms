#pragma once

#include "modules/selection_sort_family/selection_sort.hpp"
#include "test/tester.hpp"

void test_selection_sort()
{
	auto tester = Tester<mak::selection_sort>("selection sort");
	tester.test(
		{ 1 },
		{ 1, 1, 1, 1, 1 },
		{ 9, 8, 7, 6, 3, 2 },
		{ 1, 3, 6, 8, 9 },
		{ 6, 3, -1, -7, 0, 9, 8, 2 },
		{ -3, 1, 2, 0, 9, 8, 6 }
	);
}
