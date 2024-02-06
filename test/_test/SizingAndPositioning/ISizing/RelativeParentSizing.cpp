#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/RelativeParentSizing/RelativeParentSizing.hpp>

TEST(SizingAndPositioning, RelativeParentSizing) {
	ie::RelativeParentSizing relative_parent_sizing{{2}, 17};
	
	ASSERT_FLOAT_EQ(relative_parent_sizing.find_size(7, 51), 9);
	ASSERT_FLOAT_EQ(relative_parent_sizing.get_parent_size(23), 21);
}