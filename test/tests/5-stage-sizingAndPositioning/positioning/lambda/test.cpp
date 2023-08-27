#include <gtest/gtest.h>
#include <../../../../../lib/IE/SizingAndPositioning/positioning/LambdaPositioning2/LambdaPositioning.hpp>

TEST(LambdaPositioning, base) {
	ie::LambdaPositioning lambdaPositioning{[](float, float, float, float) -> float {return 13;}};
	ASSERT_EQ((lambdaPositioning(0, 0, 0, 0)), 13);
}

TEST(LambdaPositioning, copy) {
	ie::LambdaPositioning lambdaPositioning{[](float, float, float, float) -> float {return 13;}};
	ie::LambdaPositioning* copyLambdaPositioning{lambdaPositioning.copy()};
	ASSERT_EQ((lambdaPositioning.findPosition(0, 0, 0, 0)), 13);
}