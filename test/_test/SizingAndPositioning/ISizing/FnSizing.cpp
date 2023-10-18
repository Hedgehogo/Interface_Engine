#include <gtest/gtest.h>
#include "IE/sizing-positioning/ISizing/FnSizing/FnSizing.hpp"

TEST(SizingAndPositioning, FnSizing) {
	ie::FnSizing fn_sizing{
		{
			[](float, float, float) {
				return 13.f;
			},
			[](float) {
				return 5.f;
			}
		}, 17
	};
	
	ASSERT_FLOAT_EQ(fn_sizing.find_size(7, 51), 13);
	ASSERT_FLOAT_EQ(fn_sizing.get_parent_size(23), 5.f);
}