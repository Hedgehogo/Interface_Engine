#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing/SmartSizing/SmartSizing.hpp>

TEST(SizingAndPositioning, SmartSizing) {
	ui::SmartSizing parentCoefficientSizing{{0.5, 0.5, 1}, 17};
	
	ASSERT_FLOAT_EQ(parentCoefficientSizing.findSize(7, 51), 30);
	ASSERT_FLOAT_EQ(parentCoefficientSizing.getParentSize(23), 44);
}