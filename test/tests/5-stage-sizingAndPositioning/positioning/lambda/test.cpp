#include <gtest/gtest.h>
#include <../../../../../lib/IE/sizing-positioning/positioning/FnPositioning2/FnPositioning.hpp>

TEST(FnPositioning, base) {
	ie::FnPositioning lambdaPositioning{[](float, float, float, float) -> float {return 13;}};
	ASSERT_EQ((lambdaPositioning(0, 0, 0, 0)), 13);
}

TEST(FnPositioning, copy) {
	ie::FnPositioning lambdaPositioning{[](float, float, float, float) -> float {return 13;}};
	ie::FnPositioning* copyFnPositioning{lambdaPositioning.copy()};
	ASSERT_EQ((lambdaPositioning.findPosition(0, 0, 0, 0)), 13);
}