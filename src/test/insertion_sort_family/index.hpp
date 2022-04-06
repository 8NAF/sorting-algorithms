#pragma once

#if mak_insertion_family==1 || mak_binary_insertion==1
#include "binary_insertion_sort.test.hpp"
#endif
#if mak_insertion_family==1 || mak_insertion==1
#include "insertion_sort.test.hpp"
#endif
#if mak_insertion_family==1 || mak_shell==1
#include "shell_sort.test.hpp"
#endif

void test_insertion_sort_family()
{
#if mak_insertion_family==1 || mak_binary_insertion==1
	test_binary_insertion_sort();
#endif
#if mak_insertion_family==1 || mak_insertion==1
	test_insertion_sort();
#endif
#if mak_insertion_family==1 || mak_shell==1
	test_shell_sort();
#endif
}
