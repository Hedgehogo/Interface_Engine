#include <gtest/gtest.h>
#include <../../../../../lib/ui/sizingAndPositioning/positioning/lambda/lambdaPositioning.hpp>

TEST(LambdaPositioning, base) {
	ui::LambdaPositioning lambdaPositioning{[](float, float, float, float) -> float {return 13;}};
	ASSERT_EQ((lambdaPositioning(0, 0, 0, 0)), 13);
}

TEST(LambdaPositioning, copy) {
	ui::LambdaPositioning lambdaPositioning{[](float, float, float, float) -> float {return 13;}};
	ui::LambdaPositioning* copyLambdaPositioning{lambdaPositioning.copy()};
	ASSERT_EQ((lambdaPositioning.findPosition(0, 0, 0, 0)), 13);
}