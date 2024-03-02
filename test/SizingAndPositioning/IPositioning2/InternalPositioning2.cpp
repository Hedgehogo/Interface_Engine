#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning2/InternalPositioning2/InternalPositioning2.hpp>

TEST(SizingAndPositioning, InternalPositioning2) {
	ie::InternalPositioning2 internal_positioning2{{0.5, 0.5}};
	
	ASSERT_EQ(
		internal_positioning2.find_position({12, 17}, {27, 31}, {16, 19}),
		(sf::Vector2f{17.5, 23})
	);
}