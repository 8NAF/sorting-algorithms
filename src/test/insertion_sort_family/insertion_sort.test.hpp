#pragma once

#include "modules/insertion_sort_family/insertion_sort.hpp"
#include "test/tester.hpp"

void test_insertion_sort()
{
	auto tester = Tester<mak::insertion_sort>("insertion sort");
	tester.test(
		{ 1 },
		{ 5, 5, 5, 5, 5 },
		{ 1, 2, 3, 4, 5, 6 },
		{ 6, 5, 4, 3, 2, 1 },
		{ 5, 2, 1, 8, 7, 0 },
		{ -2, -1, -1, -5, -3, -9, -5 }
	);
}
