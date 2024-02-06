#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/RelativeNormalSizing/RelativeNormalSizing.hpp>

TEST(SizingAndPositioning, RelativeNormalSizing) {
	ie::RelativeNormalSizing relative_normal_sizing{{}, 17};
	
	ASSERT_FLOAT_EQ(relative_normal_sizing.find_size(7, 51), 17);
	ASSERT_FLOAT_EQ(relative_normal_sizing.get_parent_size(23), 0);
}