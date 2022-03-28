#pragma once

#include "modules/radix_sort_family/counting_sort.hpp"
#include "test/tester.hpp"

void test_counting_sort()
{
	auto tester = Tester<mak::counting_sort>("counting sort");
	tester.test(
		{ 1 },
		{ -1, -1, -1, -1 },
		{ -9, -5, -3, 0, 3, 5, 6 },
		{ 9, 7, 3, 2, -1, -4, -8 },
		{ 5, 6, 7, 1, 6, 8, 3, 3 },
		{ -9, -1, -8, -4, -3, -7, -7, -1 }
	);
}
