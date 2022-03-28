#pragma once

#include "modules/tree_sort_family/tree_sort.hpp"
#include "test/tester.hpp"

void test_tree_sort()
{
	auto tester = Tester<mak::tree_sort>("tree sort");
	tester.test(
		{ 1 },
		{ 4, 4, 4, 4, 4 },
		{ -4, -3, -2, -1, 0 },
		{ 9, 7, 5, 3, 1 },
		{ -8, -1, -9, 0, 6, 2, 3 },
		{ 1, 3, 9, 7, -5, -5, 0 }
	);
}
