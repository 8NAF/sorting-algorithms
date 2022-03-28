#pragma once

#include "modules/insertion_sort_family/binary_insertion_sort.hpp"
#include "test/tester.hpp"

void test_binary_insertion_sort()
{
	auto tester = Tester<mak::binary_insertion_sort>("binary insertion sort");
	tester.test(
		{ 1 },
		{ 4, 4, 4, 4, 4 },
		{ 1, 2, 3, 4, 5, 6 },
		{ 6, 5, 4, 3, 2, 1 },
		{ 3, 1, 9, 8, -1, -5, -6, -7, -2 },
		{ 6, 1, -7, 1, 6, -7, 8, -9, -2 }
	);
}
