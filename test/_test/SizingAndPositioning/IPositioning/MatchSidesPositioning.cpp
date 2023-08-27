#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/IPositioning/MatchSidesPositioning/MatchSidesPositioning.hpp>

TEST(SizingAndPositioning, MatchSidesPositioning) {
	ie::MatchSidesPositioning matchSidesPositioning{ie::Location::center, ie::Location::origin, 0.5};
	
	ASSERT_FLOAT_EQ(matchSidesPositioning.findPosition(12, 27, 16, 51), 20.5);
}