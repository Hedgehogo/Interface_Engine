#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning/MatchPositioning/MatchPositioning.hpp>

TEST(SizingAndPositioning, MatchPositioning) {
	ie::MatchPositioning matchPositioning{0.5, 0.0, 0.5};
	
	ASSERT_FLOAT_EQ(matchPositioning.findPosition(12, 27, 16, 51), 20.5);
}