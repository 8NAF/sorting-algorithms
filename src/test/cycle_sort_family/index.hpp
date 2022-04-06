#pragma once

#if mak_cycle_family==1 || mak_cycle==1
#include "cycle_sort.test.hpp"
#endif

void test_cycle_sort_family()
{
#if mak_cycle_family==1 || mak_cycle==1
	test_cycle_sort();
#endif
}
