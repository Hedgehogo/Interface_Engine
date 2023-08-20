#include <gtest/gtest.h>
#include <../../../../../lib/IE/sizingAndPositioning/positioning/internal/target/internalTargetPositioning.hpp>


TEST(InternalTargetPositioning, base) {
	{
		ui::InternalTargetPositioning internalPositioning{0};
		ASSERT_EQ((internalPositioning(0, 2, 0, 4)), 0.f);
		ASSERT_EQ((internalPositioning(0, 4, 0, 2)), 0.f);
	}
	{
		ui::InternalTargetPositioning internalPositioning{0, 4};
		ASSERT_EQ((internalPositioning(0, 2, 0, 4)), 4.f);
		ASSERT_EQ((internalPositioning(0, 4, 0, 2)), 4.f);
	}
	{
		ui::InternalTargetPositioning internalPositioning{0.5};
		ASSERT_EQ((internalPositioning(0, 2, 0, 4)), 1.f);
		ASSERT_EQ((internalPositioning(0, 4, 0, 2)), -1.f);
	}
	{
		ui::InternalTargetPositioning internalPositioning{0.5, 4};
		ASSERT_EQ((internalPositioning(0, 2, 0, 4)), 5.f);
		ASSERT_EQ((internalPositioning(0, 4, 0, 2)), 3.f);
	}
}

TEST(InternalTargetPositioning, copy) {
	ui::InternalTargetPositioning internalTargetPositioning{1, 2};
	ui::InternalTargetPositioning* copyInternalTargetPositioning{internalTargetPositioning.copy()};

	ASSERT_EQ(copyInternalTargetPositioning->getCoefficient(), 1);
	ASSERT_EQ(copyInternalTargetPositioning->getOffset(), 2);
}
