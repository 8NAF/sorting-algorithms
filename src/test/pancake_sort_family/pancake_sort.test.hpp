#include "test/tester.hpp"
#include "modules/pancake_sort_family/index.hpp"

void test_pancake_sort()
{
	Printer::print_color<colors::fg_blue>("\n[########## PANCAKE SORT ##########]\n");

	auto tester = Tester<mak::pancake_sort>();

	std::initializer_list<int> i1 = {};
	std::initializer_list<int> i2 = { 3 };
	std::initializer_list<int> i3 = { -3, -4, -6, -7, -7, -8, -1, 0, -2, -5 };
	tester.test_std_vector(i1, i2, i3);
	tester.test_std_list(i1, i2, i3);
	tester.test_std_deque(i1, i2, i3);
	//tester.test_std_forward_list(i1, i2, i3);

	tester.test_std_array(
		std::array<int, 0>{},
		std::to_array({ 3 }),
		std::to_array({ -3, -4, -6, -7, -7, -8, -1, 0, -2, -5 })
	);

	tester.test_static_array(
		{ 3 },
		{ -3, -4, -6, -7, -7, -8, -1, 0, -2, -5 }
	);

	tester.test_dynamic_array<0, 1, 10>(
		new int[] {},
		new int[] {3},
		new int[] {-3, -4, -6, -7, -7, -8, -1, 0, -2, -5}
	);

	Printer::print_color<colors::fg_blue>("\n[#################################]\n");
}
