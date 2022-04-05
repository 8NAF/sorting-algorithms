#include "./bubble_sort_family/index.hpp"
#include "./cycle_sort_family/index.hpp"
#include "./heap_sort_family/index.hpp"
#include "./hybrid_sort_family/index.hpp"
#include "./insertion_sort_family/index.hpp"
#include "./pancake_sort_family/index.hpp"
#include "./quick_sort_family/index.hpp"
#include "./radix_sort_family/index.hpp"
#include "./selection_sort_family/index.hpp"
#include "./tree_sort_family/index.hpp"

int main()
{
	test_bubble_sort_family();
	test_cycle_sort_family();
	test_heap_sort_family();
	test_hybrid_sort_family();
	test_insertion_sort_family();
	test_pancake_sort_family();
	test_quick_sort_family();
	test_radix_sort_family();
	test_selection_sort();
	test_tree_sort_family();

	return 0;
}
