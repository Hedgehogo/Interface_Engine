#include <gtest/gtest.h>
#include <../../../../../lib/IE/updatable/manager/updateManager.hpp>
#include "../../../testsObjects/testObject/testObject.hpp"

TEST(UpdateManager, draw_and_add) {
	TestObject testObject{};
	ui::UpdateManager updateManager;
	updateManager.add(testObject);
	updateManager.update();
	ASSERT_GT(testObject.getProcessed().update, 0);
}

TEST(UpdateManager, clear) {
	TestObject testObject{};
	ui::UpdateManager updateManager;
	updateManager.add(testObject);
	updateManager.clear();
	updateManager.update();
	ASSERT_EQ(testObject.getProcessed().update, 0);
}
