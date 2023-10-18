#include <gtest/gtest.h>
#include <../../../../../lib/IE/sizing-positioning/positioning/FnPositioning2/FnPositioning.hpp>

TEST(FnPositioning, base) {
	ie::FnPositioning lambda_positioning{[](float, float, float, float) -> float {return 13;}};
	ASSERT_EQ((lambda_positioning(0, 0, 0, 0)), 13);
}

TEST(FnPositioning, copy) {
	ie::FnPositioning lambda_positioning{[](float, float, float, float) -> float {return 13;}};
	ie::FnPositioning* copy_fn_positioning{lambda_positioning.copy()};
	ASSERT_EQ((lambda_positioning.find_position(0, 0, 0, 0)), 13);
}