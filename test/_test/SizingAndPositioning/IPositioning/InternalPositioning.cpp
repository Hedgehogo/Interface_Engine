#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning/InternalPositioning/InternalPositioning.hpp>

TEST(SizingAndPositioning, InternalPositioning) {
	ie::InternalPositioning internal_positioning{0.5, 0.5};
	
	ASSERT_FLOAT_EQ(internal_positioning.find_position(12, 27, 16, 51), 7);
}