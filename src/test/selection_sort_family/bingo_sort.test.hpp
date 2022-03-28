#pragma once

#include "modules/selection_sort_family/bingo_sort.hpp"
#include "test/tester.hpp"

void test_bingo_sort()
{
	auto tester = Tester<mak::bingo_sort>("bingo sort");
	tester.test(
		{ 1 },
		{ 1, 1, 1, 1, 1 },
		{ 9, 8, 7, 6, 3, 2 },
		{ 1, 3, 6, 8, 9 },
		{ 6, 7, 1, -6, 3, 1, -9, -6, 5 },
		{ 4, 1, 1, -5, 3, -2, 7, 6, -3 }
	);
}
