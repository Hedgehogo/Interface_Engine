#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning/MatchSidesPositioning/MatchSidesPositioning.hpp>

TEST(SizingAndPositioning, MatchSidesPositioning) {
	ie::MatchSidesPositioning match_sides_positioning{ie::Location::Center, ie::Location::Origin, 0.5};
	
	ASSERT_FLOAT_EQ(match_sides_positioning.find_position(12, 27, 16, 51), 20.5);
}