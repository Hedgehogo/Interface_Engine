#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing/LambdaSizing/LambdaSizing.hpp>

TEST(SizingAndPositioning, LambdaSizing) {
	ui::LambdaSizing lambdaSizing{
		{
			[](float, float, float) {
				return 13.f;
			},
			[](float) {
				return 5.f;
			}
		}, 17
	};
	
	ASSERT_FLOAT_EQ(lambdaSizing.findSize(7, 51), 13);
	ASSERT_FLOAT_EQ(lambdaSizing.getParentSize(23), 5.f);
}