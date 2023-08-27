#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/IPositioning/LambdaPositioning/LambdaPositioning.hpp>

TEST(SizingAndPositioning, LambdaPositioning) {
	ie::LambdaPositioning lambdaPositioning{
		[](float, float, float, float) {
			return 15.f;
		}
	};
	
	ASSERT_FLOAT_EQ(lambdaPositioning.findPosition(12, 27, 16, 51), 15);
}