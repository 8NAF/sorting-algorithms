#pragma once

#if mak_bubble_family==1 || mak_bubble==1
#include "bubble_sort.test.hpp"
#endif
#if mak_bubble_family==1 || mak_cocktail==1
#include "cocktail_shaker_sort.test.hpp"
#endif
#if mak_bubble_family==1 || mak_comb==1
#include "comb_sort.test.hpp"
#endif
#if mak_bubble_family==1 || mak_odd_even==1
#include "odd_even_sort.test.hpp"
#endif

void test_bubble_sort_family()
{
#if mak_bubble_family==1 || mak_bubble==1
	test_bubble_sort();
#endif
#if mak_bubble_family==1 || mak_cocktail==1
	test_cocktail_shaker_sort();
#endif
#if mak_bubble_family==1 || mak_comb==1
	test_comb_sort();
#endif
#if mak_bubble_family==1 || mak_odd_even==1
	test_odd_even_sort();
#endif
}
