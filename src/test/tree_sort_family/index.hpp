#pragma once

#if mak_tree_family==1 || mak_tree==1
#include "tree_sort.test.hpp"
#endif

void test_tree_sort_family()
{
#if mak_tree_family==1 || mak_tree==1
	test_tree_sort();
#endif
}
