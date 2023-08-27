#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing/TargetCoefficientSizing/TargetCoefficientSizing.hpp>

TEST(SizingAndPositioning, TargetCoefficientSizing) {
	ie::TargetCoefficientSizing targetCoefficientSizing{{0.5, 0.5}, 17};
	
	ASSERT_FLOAT_EQ(targetCoefficientSizing.findSize(7, 51), 26);
	ASSERT_FLOAT_EQ(targetCoefficientSizing.getParentSize(23), 0);
}