#include <gtest/gtest.h>
#include <../../../../../lib/IE/component/IDrawable/DrawManager/DrawManager.hpp>
#include "../../../testsObjects/testObject/testObject.hpp"

TEST(DrawManager, draw_and_add) {
	TestObject testObject{};
	ie::DrawManager drawManager;
	drawManager.add(testObject);
	drawManager.draw();
	ASSERT_GT(testObject.getProcessed().draw, 0);
}

TEST(DrawManager, clear) {
	TestObject testObject{};
	ie::DrawManager drawManager;
	drawManager.add(testObject);
	drawManager.clear();
	drawManager.draw();
	ASSERT_EQ(testObject.getProcessed().draw, 0);
}
