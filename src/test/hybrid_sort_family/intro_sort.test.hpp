#pragma once

#include "modules/hybrid_sort_family/intro_sort.hpp"
#include "test/tester.hpp"

void test_intro_sort()
{
	auto tester = Tester<mak::intro_sort>("intro sort");
	tester.test(
		{ 1 },
		{ 9, 9, 9, 9, 9 },
		{ 1, 2, 3, 4, 5, 6 },
		{ 6, 5, 4, 3, 2, 1 },
		{ 2, 5, 1, 0, -3, -4, -4 },
		{ 6, 1, 9, 0, -1, -2 }
	);
}
