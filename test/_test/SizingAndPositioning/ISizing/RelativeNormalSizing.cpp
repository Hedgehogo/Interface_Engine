#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/RelativeNormalSizing/RelativeNormalSizing.hpp>

TEST(SizingAndPositioning, RelativeNormalSizing) {
	ie::RelativeNormalSizing relativeNormalSizing{{}, 17};
	
	ASSERT_FLOAT_EQ(relativeNormalSizing.findSize(7, 51), 17);
	ASSERT_FLOAT_EQ(relativeNormalSizing.getParentSize(23), 0);
}