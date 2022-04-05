#pragma once

#include "iterative_quick_sort.test.hpp"
#include "quick_sort.test.hpp"

void test_quick_sort_family()
{
	test_iterative_quick_sort();
	test_quick_sort();
}
