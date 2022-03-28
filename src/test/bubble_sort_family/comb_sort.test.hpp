#pragma once

#include "modules/bubble_sort_family/comb_sort.hpp"
#include "test/tester.hpp"

void test_comb_sort()
{
	auto tester = Tester<mak::comb_sort>("comb sort");
	tester.test(
		{ 1 },
		{ -3, -3, -3, -3, -3 },
		{ -1, -2, -3, -4, -5, -6 },
		{ -6, -5, -4, -3, -2, -1 },
		{ 2, 2, 1, 1, 3, 3, 6, 6, 5, 5 },
		{ 9, 8, 7, 1, 0, 3, 3 }
	);
}
