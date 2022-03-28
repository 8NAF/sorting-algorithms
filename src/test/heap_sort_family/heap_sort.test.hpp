#pragma once

#include "modules/heap_sort_family/heap_sort.hpp"
#include "test/tester.hpp"

void test_heap_sort()
{
	auto tester = Tester<mak::heap_sort>("heap sort");
	tester.test(
		{ 1 },
		{ 8, 8, 8, 8, 8 },
		{ 1, 2, 3, 4, 5, 6 },
		{ 6, 5, 4, 3, 2, 1 },
		{ 5, 1, -8, 7, -5, -3, -2 },
		{ 1, 2, 5, -7, -8, -9 }
	);
}
