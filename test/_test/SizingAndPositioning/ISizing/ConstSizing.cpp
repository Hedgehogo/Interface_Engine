#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing/ConstSizing/ConstSizing.hpp>

TEST(SizingAndPositioning, ConstSizing) {
	ui::ConstSizing constSizing{{13}, 17};
	
	ASSERT_FLOAT_EQ(constSizing.findSize(7, 51), 13);
	ASSERT_FLOAT_EQ(constSizing.getParentSize(23), 0);
}