#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing/RelativeNormalSizing/RelativeNormalSizing.hpp>

TEST(SizingAndPositioning, RelativeNormalSizing) {
	ui::RelativeNormalSizing relativeNormalSizing{{}, 17};
	
	ASSERT_FLOAT_EQ(relativeNormalSizing.findSize(7, 51), 17);
	ASSERT_FLOAT_EQ(relativeNormalSizing.getParentSize(23), 0);
}