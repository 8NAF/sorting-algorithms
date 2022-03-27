#include "test/tester.hpp"
#include "modules/insertion_sort_family/index.hpp"

void test_binary_insertion_sort()
{

	Printer::print_color<colors::fg_blue>("\n[########## BINARY INSERTION SORT ##########]\n");

	auto tester = Tester<mak::binary_insertion_sort>();

	std::initializer_list<int> i1 = {};
	std::initializer_list<int> i2 = { 3 };
	std::initializer_list<int> i3 = { -6, 1, -5, 1, 1, 0, -5, 2, 1, 9, 9, -5, -4, -3, 0, 0, 8 };
	tester.test_std_vector(i1, i2, i3);
	tester.test_std_list(i1, i2, i3);
	tester.test_std_deque(i1, i2, i3);
	//tester.test_std_forward_list(i1, i2, i3);

	tester.test_std_array(
		std::array<int, 0>{},
		std::to_array({ 3 }),
		std::to_array({ -6, 1, -5, 1, 1, 0, -5, 2, 1, 9, 9, -5, -4, -3, 0, 0, 8 })
	);

	tester.test_static_array(
		{ 3 },
		{ -6, 1, -5, 1, 1, 0, -5, 2, 1, 9, 9, -5, -4, -3, 0, 0, 8 }
	);

	tester.test_dynamic_array<0, 1, 17>(
		new int[] {},
		new int[] { 3 },
		new int[] {-6, 1, -5, 1, 1, 0, -5, 2, 1, 9, 9, -5, -4, -3, 0, 0, 8 }
	);

	Printer::print_color<colors::fg_blue>("\n[#################################]\n");
}
