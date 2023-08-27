#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/IPositioning/InternalPositioning/InternalPositioning.hpp>

TEST(SizingAndPositioning, InternalPositioning) {
	ie::InternalPositioning internalPositioning{0.5, 0.5};
	
	ASSERT_FLOAT_EQ(internalPositioning.findPosition(12, 27, 16, 51), 7);
}