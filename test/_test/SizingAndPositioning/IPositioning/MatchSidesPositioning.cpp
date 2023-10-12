#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning/MatchSidesPositioning/MatchSidesPositioning.hpp>

TEST(SizingAndPositioning, MatchSidesPositioning) {
	ie::MatchSidesPositioning matchSidesPositioning{ie::Location::Center, ie::Location::Origin, 0.5};
	
	ASSERT_FLOAT_EQ(matchSidesPositioning.findPosition(12, 27, 16, 51), 20.5);
}