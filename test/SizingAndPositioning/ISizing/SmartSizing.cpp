#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/SmartSizing/SmartSizing.hpp>

TEST(SizingAndPositioning, SmartSizing) {
	ie::SmartSizing parent_coefficient_sizing{{0.5, 0.5, 1}, 17};
	
	ASSERT_FLOAT_EQ(parent_coefficient_sizing.find_size(7, 51), 30);
	ASSERT_FLOAT_EQ(parent_coefficient_sizing.get_parent_size(23), 44);
}