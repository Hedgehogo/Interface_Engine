#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/ConstSizing/ConstSizing.hpp>

TEST(SizingAndPositioning, ConstSizing) {
	ie::ConstSizing const_sizing{{13}, 17};
	
	ASSERT_FLOAT_EQ(const_sizing.find_size(7, 51), 13);
	ASSERT_FLOAT_EQ(const_sizing.get_parent_size(23), 0);
}