#pragma once

#include "modules/cycle_sort_family/cycle_sort.hpp"
#include "test/tester.hpp"

void test_cycle_sort()
{
	auto tester = Tester<mak::cycle_sort>("cycle sort");
	tester.test(
		{ 1 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 2, 3, 4, 5, 6 },
		{ 6, 5, 4, 3, 2, 1 },
		{ 2, -9, 1, -5, 1, -5, 6, 3, 3, -1 },
		{ 4, 1, -7, 8, 1, 1, 3, 5 }
	);
}
