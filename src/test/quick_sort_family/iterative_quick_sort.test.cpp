#include "test/tester.hpp"
#include "modules/quick_sort_family/index.hpp"

int main()
{

	Printer::print_color<colors::fg_blue>("\n[########## ITERATIVE QUICK SORT ##########]\n");

	auto tester = Tester<mak::iterative_quick_sort>();

	std::initializer_list<int> i1 = {};
	std::initializer_list<int> i2 = { 3 };
	std::initializer_list<int> i3 = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	tester.test_std_vector(i1, i2, i3);
	tester.test_std_list(i1, i2, i3);
	tester.test_std_deque(i1, i2, i3);
	//tester.test_std_forward_list(i1, i2, i3);

	tester.test_std_array(
		std::array<int, 0>{},
		std::to_array({ 3 }),
		std::to_array({ 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 })
	);

	tester.test_static_array(
		{ 3 },
		{ 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 }
	);

	tester.test_dynamic_array<0, 1, 10>(
		new int[] {},
		new int[] { 3 },
		new int[] {1, 2, 3, 4, 5, 5, 4, 3, 2, 1 }
	);

	Printer::print_color<colors::fg_blue>("\n[#################################]\n");
}
