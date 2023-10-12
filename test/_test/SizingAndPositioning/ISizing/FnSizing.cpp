#include <gtest/gtest.h>
#include "IE/sizing-positioning/ISizing/FnSizing/FnSizing.hpp"

TEST(SizingAndPositioning, FnSizing) {
	ie::FnSizing fnSizing{
		{
			[](float, float, float) {
				return 13.f;
			},
			[](float) {
				return 5.f;
			}
		}, 17
	};
	
	ASSERT_FLOAT_EQ(fnSizing.findSize(7, 51), 13);
	ASSERT_FLOAT_EQ(fnSizing.getParentSize(23), 5.f);
}