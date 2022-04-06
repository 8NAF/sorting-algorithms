#pragma once

#if mak_selection_family==1 || mak_bingo==1
#include "bingo_sort.test.hpp"
#endif
#if mak_selection_family==1 || mak_double_selection==1
#include "double_selection_sort.test.hpp"
#endif
#if mak_selection_family==1 || mak_selection==1
#include "selection_sort.test.hpp"
#endif

void test_selection_sort_family()
{
#if mak_selection_family==1 || mak_bingo==1
	test_bingo_sort();
#endif
#if mak_selection_family==1 || mak_double_selection==1
	test_double_selection_sort();
#endif
#if mak_selection_family==1 || mak_selection==1
	test_selection_sort();
#endif
}
