#include <gtest/gtest.h>
#include "IE/Animation/IChangeVariable/strainghtLine/changeVariableByStraightLine.hpp"

TEST(ChangeVariableByStraightLine, operator) {
	ui::ChangeVariableByStraightLine changeVariableByStraightLine{0.5, 6, 3};

	ASSERT_EQ(changeVariableByStraightLine(0), 3);
	ASSERT_EQ(changeVariableByStraightLine(3), 4.5);
	ASSERT_EQ(changeVariableByStraightLine(6), 6);
}

TEST(ChangeVariableByStraightLine, getSize) {
	ui::ChangeVariableByStraightLine changeVariableByStraightLine{1, 2};
	ASSERT_EQ(changeVariableByStraightLine.getSize(), 2);
}

TEST(ChangeVariableByStraightLine, copy) {
	ui::IChangeVariable *changeVariable{new ui::ChangeVariableByStraightLine{0.5, 6, 3}},
      *copyChangeVariable{changeVariable->copy()};

	ASSERT_EQ(copyChangeVariable->getSize(), 6);
	ASSERT_EQ((*copyChangeVariable)(0), 3);
	ASSERT_EQ((*copyChangeVariable)(3), 4.5);
	ASSERT_EQ((*copyChangeVariable)(6), 6);

	delete copyChangeVariable;
	delete changeVariable;
}

TEST(ChangeVariableByStraightLine, make) {
	ui::IChangeVariable *changeVariable{ui::makeChangeVariableByStraightLine(3, 6, 6)};

	ASSERT_EQ(changeVariable->getSize(), 6);
	ASSERT_EQ((*changeVariable)(0), 3);
	ASSERT_EQ((*changeVariable)(3), 4.5);
	ASSERT_EQ((*changeVariable)(6), 6);

	delete changeVariable;
}