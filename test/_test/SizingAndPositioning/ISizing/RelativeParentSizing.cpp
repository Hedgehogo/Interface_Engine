#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing/RelativeParentSizing/RelativeParentSizing.hpp>

TEST(SizingAndPositioning, RelativeParentSizing) {
	ui::RelativeParentSizing relativeParentSizing{{2}, 17};
	
	ASSERT_FLOAT_EQ(relativeParentSizing.findSize(7, 51), 9);
	ASSERT_FLOAT_EQ(relativeParentSizing.getParentSize(23), 21);
}