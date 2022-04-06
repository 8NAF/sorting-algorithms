#pragma once

#if mak_heap_family==1 || mak_heap==1
#include "heap_sort.test.hpp"
#endif

void test_heap_sort_family()
{
#if mak_heap_family==1 || mak_heap==1
	test_heap_sort();
#endif
}
