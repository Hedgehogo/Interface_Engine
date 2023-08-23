#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/IPositioning/InternalTargetPositioning/InternalTargetPositioning.hpp>

TEST(SizingAndPositioning, InternalTargetPositioning) {
	ui::InternalTargetPositioning internalTargetPositioning{0.5, 0.5};
	
	ASSERT_FLOAT_EQ(internalTargetPositioning.findPosition(12, 27, 16, 51), 12.5);
}