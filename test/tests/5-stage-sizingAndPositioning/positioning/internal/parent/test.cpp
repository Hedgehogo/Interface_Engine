#include <gtest/gtest.h>
#include <../../../../../lib/IE/sizing-positioning/positioning/internal/parent/internalPositioning.hpp>

TEST(InternalPositioning, base) {
	{
		ie::InternalPositioning internalPositioning{0};
		ASSERT_EQ((internalPositioning.findPosition(0, 2, 4, 0)), 0.f);
		ASSERT_EQ((internalPositioning.findPosition(0, 4, 2, 0)), 0.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 2, 4, 0)), 3.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 4, 2, 0)), 3.f);
	}
	{
		ie::InternalPositioning internalPositioning{0, 4};
		ASSERT_EQ((internalPositioning.findPosition(0, 2, 4, 0)), 4.f);
		ASSERT_EQ((internalPositioning.findPosition(0, 4, 2, 0)), 4.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 2, 4, 0)), 7.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 4, 2, 0)), 7.f);
	}
	{
		ie::InternalPositioning internalPositioning{0.5};
		ASSERT_EQ((internalPositioning.findPosition(0, 2, 4, 0)), 1.f);
		ASSERT_EQ((internalPositioning.findPosition(0, 4, 2, 0)), -1.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 2, 4, 0)), 4.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 4, 2, 0)), 2.f);
	}
	{
		ie::InternalPositioning internalPositioning{0.5, 4};
		ASSERT_EQ((internalPositioning.findPosition(0, 2, 4, 0)), 5.f);
		ASSERT_EQ((internalPositioning.findPosition(0, 4, 2, 0)), 3.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 2, 4, 0)), 8.f);
		ASSERT_EQ((internalPositioning.findPosition(3, 4, 2, 0)), 6.f);
	}
}

TEST(InternalPositioning, copy) {
	ie::InternalPositioning internalPositioning{1, 2};
	ie::InternalPositioning* copyInternalPositioning{internalPositioning.copy()};

	ASSERT_EQ(copyInternalPositioning->getCoefficient(), 1);
	ASSERT_EQ(copyInternalPositioning->getOffset(), 2);
}
