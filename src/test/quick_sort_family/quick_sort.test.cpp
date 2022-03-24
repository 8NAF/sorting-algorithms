#include "test/tester.hpp"
#include "modules/quick_sort_family/index.hpp"

int main()
{

	Printer::print_color<colors::fg_blue>("\n[########## QUICK SORT ##########]\n");

	auto tester = Tester<mak::quick_sort>();

	std::initializer_list<int> i1 = {};
	std::initializer_list<int> i2 = { 3 };
	std::initializer_list<int> i3 = { -1, -3, -2, 7, 1, 9, 8, 0, 4, 5 };
	tester.test_std_vector(i1, i2, i3);
	tester.test_std_list(i1, i2, i3);
	tester.test_std_deque(i1, i2, i3);
	//tester.test_std_forward_list(i1, i2, i3);

	tester.test_std_array(
		std::array<int, 0>{},
		std::to_array({ 3 }),
		std::to_array({ -1, -3, -2, 7, 1, 9, 8, 0, 4, 5 })
	);

	tester.test_static_array(
		{ 3 },
		{ -1, -3, -2, 7, 1, 9, 8, 0, 4, 5 }
	);

	tester.test_dynamic_array<0, 1, 10>(
		new int[] {},
		new int[] { 3 },
		new int[] {-1, -3, -2, 7, 1, 9, 8, 0, 4, 5 }
	);

	Printer::print_color<colors::fg_blue>("\n[#################################]\n");
}
