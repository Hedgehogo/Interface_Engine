#include <gtest/gtest.h>
#include <../../../../../lib/IE/sizing-positioning/positioning/internal/parent/internal_positioning.hpp>

TEST(InternalPositioning, base) {
	{
		ie::InternalPositioning internal_positioning{0};
		ASSERT_EQ((internal_positioning.find_position(0, 2, 4, 0)), 0.f);
		ASSERT_EQ((internal_positioning.find_position(0, 4, 2, 0)), 0.f);
		ASSERT_EQ((internal_positioning.find_position(3, 2, 4, 0)), 3.f);
		ASSERT_EQ((internal_positioning.find_position(3, 4, 2, 0)), 3.f);
	}
	{
		ie::InternalPositioning internal_positioning{0, 4};
		ASSERT_EQ((internal_positioning.find_position(0, 2, 4, 0)), 4.f);
		ASSERT_EQ((internal_positioning.find_position(0, 4, 2, 0)), 4.f);
		ASSERT_EQ((internal_positioning.find_position(3, 2, 4, 0)), 7.f);
		ASSERT_EQ((internal_positioning.find_position(3, 4, 2, 0)), 7.f);
	}
	{
		ie::InternalPositioning internal_positioning{0.5};
		ASSERT_EQ((internal_positioning.find_position(0, 2, 4, 0)), 1.f);
		ASSERT_EQ((internal_positioning.find_position(0, 4, 2, 0)), -1.f);
		ASSERT_EQ((internal_positioning.find_position(3, 2, 4, 0)), 4.f);
		ASSERT_EQ((internal_positioning.find_position(3, 4, 2, 0)), 2.f);
	}
	{
		ie::InternalPositioning internal_positioning{0.5, 4};
		ASSERT_EQ((internal_positioning.find_position(0, 2, 4, 0)), 5.f);
		ASSERT_EQ((internal_positioning.find_position(0, 4, 2, 0)), 3.f);
		ASSERT_EQ((internal_positioning.find_position(3, 2, 4, 0)), 8.f);
		ASSERT_EQ((internal_positioning.find_position(3, 4, 2, 0)), 6.f);
	}
}

TEST(InternalPositioning, copy) {
	ie::InternalPositioning internal_positioning{1, 2};
	ie::InternalPositioning* copy_internal_positioning{internal_positioning.copy()};

	ASSERT_EQ(copy_internal_positioning->get_coefficient(), 1);
	ASSERT_EQ(copy_internal_positioning->get_offset(), 2);
}
