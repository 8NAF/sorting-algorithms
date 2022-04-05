#pragma once

#include "bingo_sort.test.hpp"
#include "double_selection_sort.test.hpp"
#include "selection_sort.test.hpp"

void test_selection_sort_family()
{
	test_bingo_sort();
	test_double_selection_sort();
	test_selection_sort();
}
