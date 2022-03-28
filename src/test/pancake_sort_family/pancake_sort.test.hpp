#pragma once

#include "modules/pancake_sort_family/pancake_sort.hpp"
#include "test/tester.hpp"

void test_pancake_sort()
{
	auto tester = Tester<mak::pancake_sort>("pancake sort");
	tester.test(
		{ 1 },
		{ -7, -7, -7, -7 },
		{ 6, 5, 4, 3 },
		{ 1, 2, 8, 9 },
		{ 0, 0, 1, 3, -1, -4, -9 },
		{ 4, 1, -1, -7, -8 }
	);
}
