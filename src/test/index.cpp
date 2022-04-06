#if mak_all==1 || mak_bubble_family >= 1
#include "./bubble_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_cycle_family >= 1
#include "./cycle_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_heap_family >= 1
#include "./heap_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_hybrid_family >= 1
#include "./hybrid_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_insertion_family >= 1
#include "./insertion_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_pancake_family >= 1
#include "./pancake_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_quick_family >= 1
#include "./quick_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_radix_family >= 1
#include "./radix_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_selection_family >= 1
#include "./selection_sort_family/index.hpp"
#endif
#if mak_all==1 || mak_tree_family >= 1
#include "./tree_sort_family/index.hpp"
#endif

int main()
{
#if mak_all==1 || mak_bubble_family >= 1
	test_bubble_sort_family();
#endif
#if mak_all==1 || mak_cycle_family >= 1
	test_cycle_sort_family();
#endif
#if mak_all==1 || mak_heap_family >= 1
	test_heap_sort_family();
#endif
#if mak_all==1 || mak_hybrid_family >= 1
	test_hybrid_sort_family();
#endif
#if mak_all==1 || mak_insertion_family >= 1
	test_insertion_sort_family();
#endif
#if mak_all==1 || mak_pancake_family >= 1
	test_pancake_sort_family();
#endif
#if mak_all==1 || mak_quick_family >= 1
	test_quick_sort_family();
#endif
#if mak_all==1 || mak_radix_family >= 1
	test_radix_sort_family();
#endif
#if mak_all==1 || mak_selection_family >= 1
	test_selection_sort();
#endif
#if mak_all==1 || mak_tree_family >= 1
	test_tree_sort_family();
#endif
	return 0;
}
