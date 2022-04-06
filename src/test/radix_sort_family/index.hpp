#pragma once

#if mak_radix_family==1 || mak_counting==1
#include "counting_sort.test.hpp"
#endif

void test_radix_sort_family()
{
#if mak_radix_family==1 || mak_counting==1
	test_counting_sort();
#endif
}
