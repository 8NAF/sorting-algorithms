#pragma once

#if mak_hybrid_family==1 || mak_intro==1
#include "intro_sort.test.hpp"
#endif

void test_hybrid_sort_family()
{
#if mak_hybrid_family==1 || mak_intro==1
	test_intro_sort();
#endif
}
