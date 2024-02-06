#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning/MatchTargetPositioning/MatchTargetPositioning.hpp>

TEST(SizingAndPositioning, MatchTargetPositioning) {
	ie::MatchTargetPositioning match_positioning{0.5, 0.0, 0.5};
	
	ASSERT_FLOAT_EQ(match_positioning.find_position(12, 27, 16, 51), 26);
}