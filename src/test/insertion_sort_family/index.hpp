#pragma once

#include "binary_insertion_sort.test.hpp"
#include "insertion_sort.test.hpp"
#include "shell_sort.test.hpp"

void test_insertion_sort_family()
{
	test_binary_insertion_sort();
	test_insertion_sort();
	test_shell_sort();
}
