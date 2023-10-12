#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/RelativeParentSizing/RelativeParentSizing.hpp>

TEST(SizingAndPositioning, RelativeParentSizing) {
	ie::RelativeParentSizing relativeParentSizing{{2}, 17};
	
	ASSERT_FLOAT_EQ(relativeParentSizing.findSize(7, 51), 9);
	ASSERT_FLOAT_EQ(relativeParentSizing.getParentSize(23), 21);
}