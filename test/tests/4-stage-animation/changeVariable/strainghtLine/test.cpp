#include <gtest/gtest.h>
#include "IE/Animation/IChangeVariable/strainght_line/change_variable_by_straight_line.hpp"

TEST(ChangeVariableByStraightLine, operator) {
	ie::ChangeVariableByStraightLine change_variable_by_straight_line{0.5, 6, 3};

	ASSERT_EQ(change_variable_by_straight_line(0), 3);
	ASSERT_EQ(change_variable_by_straight_line(3), 4.5);
	ASSERT_EQ(change_variable_by_straight_line(6), 6);
}

TEST(ChangeVariableByStraightLine, get_size) {
	ie::ChangeVariableByStraightLine change_variable_by_straight_line{1, 2};
	ASSERT_EQ(change_variable_by_straight_line.get_size(), 2);
}

TEST(ChangeVariableByStraightLine, copy) {
	ie::IChangeVariable *change_variable{new ie::ChangeVariableByStraightLine{0.5, 6, 3}},
      *copy_change_variable{change_variable->copy()};

	ASSERT_EQ(copy_change_variable->get_size(), 6);
	ASSERT_EQ((*copy_change_variable)(0), 3);
	ASSERT_EQ((*copy_change_variable)(3), 4.5);
	ASSERT_EQ((*copy_change_variable)(6), 6);

	delete copy_change_variable;
	delete change_variable;
}

TEST(ChangeVariableByStraightLine, make) {
	ie::IChangeVariable *change_variable{ie::make_change_variable_by_straight_line(3, 6, 6)};

	ASSERT_EQ(change_variable->get_size(), 6);
	ASSERT_EQ((*change_variable)(0), 3);
	ASSERT_EQ((*change_variable)(3), 4.5);
	ASSERT_EQ((*change_variable)(6), 6);

	delete change_variable;
}