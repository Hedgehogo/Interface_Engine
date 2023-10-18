#include <gtest/gtest.h>
#include <../../../../../lib/IE/component/IDrawable/DrawManager/DrawManager.hpp>
#include "../../../tests_objects/test_object/test_object.hpp"

TEST(DrawManager, draw_and_add) {
	TestObject test_object{};
	ie::DrawManager draw_manager;
	draw_manager.add(test_object);
	draw_manager.draw();
	ASSERT_GT(test_object.get_processed().draw, 0);
}

TEST(DrawManager, clear) {
	TestObject test_object{};
	ie::DrawManager draw_manager;
	draw_manager.add(test_object);
	draw_manager.clear();
	draw_manager.draw();
	ASSERT_EQ(test_object.get_processed().draw, 0);
}
