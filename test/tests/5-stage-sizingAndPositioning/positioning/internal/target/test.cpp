#include <gtest/gtest.h>
#include <../../../../../lib/IE/sizing-positioning/positioning/internal/target/internal_target_positioning.hpp>


TEST(InternalTargetPositioning, base) {
	{
		ie::InternalTargetPositioning internal_positioning{0};
		ASSERT_EQ((internal_positioning(0, 2, 0, 4)), 0.f);
		ASSERT_EQ((internal_positioning(0, 4, 0, 2)), 0.f);
	}
	{
		ie::InternalTargetPositioning internal_positioning{0, 4};
		ASSERT_EQ((internal_positioning(0, 2, 0, 4)), 4.f);
		ASSERT_EQ((internal_positioning(0, 4, 0, 2)), 4.f);
	}
	{
		ie::InternalTargetPositioning internal_positioning{0.5};
		ASSERT_EQ((internal_positioning(0, 2, 0, 4)), 1.f);
		ASSERT_EQ((internal_positioning(0, 4, 0, 2)), -1.f);
	}
	{
		ie::InternalTargetPositioning internal_positioning{0.5, 4};
		ASSERT_EQ((internal_positioning(0, 2, 0, 4)), 5.f);
		ASSERT_EQ((internal_positioning(0, 4, 0, 2)), 3.f);
	}
}

TEST(InternalTargetPositioning, copy) {
	ie::InternalTargetPositioning internal_target_positioning{1, 2};
	ie::InternalTargetPositioning* copy_internal_target_positioning{internal_target_positioning.copy()};

	ASSERT_EQ(copy_internal_target_positioning->get_coefficient(), 1);
	ASSERT_EQ(copy_internal_target_positioning->get_offset(), 2);
}
