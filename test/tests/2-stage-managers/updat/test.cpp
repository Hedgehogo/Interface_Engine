#include <gtest/gtest.h>
#include <../../../../../lib/IE/component/IUpdatable/UpdateManager/UpdateManager.hpp>
#include "../../../tests_objects/test_object/test_object.hpp"

TEST(UpdateManager, draw_and_add) {
	TestObject test_object{};
	ie::UpdateManager update_manager;
	update_manager.add(test_object);
	update_manager.update();
	ASSERT_GT(test_object.get_processed().update, 0);
}

TEST(UpdateManager, clear) {
	TestObject test_object{};
	ie::UpdateManager update_manager;
	update_manager.add(test_object);
	update_manager.clear();
	update_manager.update();
	ASSERT_EQ(test_object.get_processed().update, 0);
}
