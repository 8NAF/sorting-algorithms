#pragma once

#if mak_pancake_family==1 || mak_pancake==1
#include "pancake_sort.test.hpp"
#endif

void test_pancake_sort_family()
{
#if mak_pancake_family==1 || mak_pancake==1
	test_pancake_sort();
#endif
}
