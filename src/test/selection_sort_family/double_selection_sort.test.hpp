#pragma once

#include "modules/selection_sort_family/double_selection_sort.hpp"
#include "test/tester.hpp"

void test_double_selection_sort()
{
	auto tester = Tester<mak::double_selection_sort>("double selection sort");
	tester.test(
		{ 1 },
		{ 1, 1, 1, 1, 1 },
		{ 9, 8, 7, 6, 3, 2 },
		{ 1, 3, 6, 8, 9 },
		{ 5, 7, 8, -1, -3, -4, -9, -8 },
		{ 2, 2, 7, 6, 5, 1, 0, 0, 9 }
	);
}
