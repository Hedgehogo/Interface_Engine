#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/ParentCoefficientSizing/ParentCoefficientSizing.hpp>

TEST(SizingAndPositioning, ParentCoefficientSizing) {
	ie::ParentCoefficientSizing parent_coefficient_sizing{{0.5, 0.5}, 17};
	
	ASSERT_FLOAT_EQ(parent_coefficient_sizing.find_size(7, 51), 4);
	ASSERT_FLOAT_EQ(parent_coefficient_sizing.get_parent_size(23), 45);
}