#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning/InternalTargetPositioning/InternalTargetPositioning.hpp>

TEST(SizingAndPositioning, InternalTargetPositioning) {
	ie::InternalTargetPositioning internal_target_positioning{0.5, 0.5};
	
	ASSERT_FLOAT_EQ(internal_target_positioning.find_position(12, 27, 16, 51), 12.5);
}