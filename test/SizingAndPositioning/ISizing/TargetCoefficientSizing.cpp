#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing/TargetCoefficientSizing/TargetCoefficientSizing.hpp>

TEST(SizingAndPositioning, TargetCoefficientSizing) {
	ie::TargetCoefficientSizing target_coefficient_sizing{{0.5, 0.5}, 17};
	
	ASSERT_FLOAT_EQ(target_coefficient_sizing.find_size(7, 51), 26);
	ASSERT_FLOAT_EQ(target_coefficient_sizing.get_parent_size(23), 0);
}