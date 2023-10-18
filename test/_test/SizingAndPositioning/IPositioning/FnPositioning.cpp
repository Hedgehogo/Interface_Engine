#include <gtest/gtest.h>
#include "IE/sizing-positioning/IPositioning/FnPositioning/FnPositioning.hpp"

TEST(SizingAndPositioning, FnPositioning) {
	ie::FnPositioning fn_positioning{
		[](float, float, float, float) {
			return 15.f;
		}
	};
	
	ASSERT_FLOAT_EQ(fn_positioning.find_position(12, 27, 16, 51), 15);
}