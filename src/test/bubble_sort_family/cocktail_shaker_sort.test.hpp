#pragma once

#include "modules/bubble_sort_family/cocktail_shaker_sort.hpp"
#include "test/tester.hpp"

void test_cocktail_shaker_sort()
{
	auto tester = Tester<mak::cocktail_shaker_sort>("cocktail shaker sort");
	tester.test(
		{ 1 },
		{ -2, -2, -2, -2, -2 },
		{ -1, -2, -3, -4, -5, -6 },
		{ -6, -5, -4, -3, -2, -1 },
		{ 4, 1, 6, 7, -2, -3, -5, -9 },
		{ 3, -1, 0, -8, 1, -7, 5, -1 }
	);
}
