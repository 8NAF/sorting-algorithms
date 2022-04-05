#pragma once

#include "bubble_sort.test.hpp"
#include "cocktail_shaker_sort.test.hpp"
#include "comb_sort.test.hpp"
#include "odd_even_sort.test.hpp"

void test_bubble_sort_family()
{
	test_bubble_sort();
	test_cocktail_shaker_sort();
	test_comb_sort();
	test_odd_even_sort();
}
