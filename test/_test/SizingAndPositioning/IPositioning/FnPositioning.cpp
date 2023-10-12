#include <gtest/gtest.h>
#include "IE/sizing-positioning/IPositioning/FnPositioning/FnPositioning.hpp"

TEST(SizingAndPositioning, FnPositioning) {
	ie::FnPositioning fnPositioning{
		[](float, float, float, float) {
			return 15.f;
		}
	};
	
	ASSERT_FLOAT_EQ(fnPositioning.findPosition(12, 27, 16, 51), 15);
}