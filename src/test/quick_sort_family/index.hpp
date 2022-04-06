#pragma once

#if mak_quick_family==1 || mak_iterative_quick==1
#include "iterative_quick_sort.test.hpp"
#endif
#if mak_quick_family==1 || mak_quick==1
#include "quick_sort.test.hpp"
#endif

void test_quick_sort_family()
{
#if mak_quick_family==1 || mak_iterative_quick==1
	test_iterative_quick_sort();
#endif
#if mak_quick_family==1 || mak_quick==1
	test_quick_sort();
#endif
}
