#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing/ParentCoefficientSizing/ParentCoefficientSizing.hpp>

TEST(SizingAndPositioning, ParentCoefficientSizing) {
	ui::ParentCoefficientSizing parentCoefficientSizing{{0.5, 0.5}, 17};
	
	ASSERT_FLOAT_EQ(parentCoefficientSizing.findSize(7, 51), 4);
	ASSERT_FLOAT_EQ(parentCoefficientSizing.getParentSize(23), 45);
}