#include "../../../create_test_program/create_test_program.hpp"
#include "../../../tests_objects/test_panel/test_panel.hpp"

TEST(PanelManager, draw_and_display_panel) {
	TestPanel test_panel{};
	ie::PanelManager panel_manager{{&test_panel}};
	panel_manager.display_panel(&test_panel);

	panel_manager.draw();

	ASSERT_GT(test_panel.get_processed().draw, 0);
}

TEST(PanelManager, draw_and_hide_panel) {
	TestPanel test_panel{};
	ie::PanelManager panel_manager{};
	panel_manager.display_panel(&test_panel);
	panel_manager.hide_panel(&test_panel);

	panel_manager.draw();

	ASSERT_EQ(test_panel.get_processed().draw, 0);
}

TEST(PanelManager, update_and_add_panel) {
	TestPanel test_panel{};
	ie::PanelManager panel_manager{};
	panel_manager.add_panel(&test_panel);

	panel_manager.update();

	ASSERT_GT(test_panel.get_processed().update, 0);
}

TEST(PanelManager, update_and_remove_panel) {
	TestPanel test_panel{};
	ie::PanelManager panel_manager{};
	panel_manager.add_panel(&test_panel);
	panel_manager.remove_panel(&test_panel);

	panel_manager.update();

	ASSERT_EQ(test_panel.get_processed().update, 0);
}

TEST(PanelManager, is_free) {
	TestPanel test_panel_not_free{false, {0, 0}, {100, 100}, false};
	TestPanel test_panel_not_free1{false, {0, 0}, {100, 100}, false};
	ie::PanelManager panel_manager{{&test_panel_not_free, &test_panel_not_free1}};
	panel_manager.display_panel(&test_panel_not_free);
	panel_manager.display_panel(&test_panel_not_free1);
	ASSERT_TRUE(panel_manager.is_free());

	TestPanel test_panel{};

	panel_manager.display_panel(&test_panel);

	ASSERT_FALSE(panel_manager.is_free());
}

TEST(PanelManager, in_const_panels) {
	TestPanel test_panel_not_free{};
	TestPanel test_panel_not_free1{};
	ie::PanelManager panel_manager{{&test_panel_not_free, &test_panel_not_free1}};
	panel_manager.display_panel(&test_panel_not_free);
	panel_manager.display_panel(&test_panel_not_free1);
	ASSERT_FALSE(panel_manager.in_const_panels({0, 0}));

	TestPanel test_panel{false, {0, 0}, {100, 100}, false};

	panel_manager.display_panel(&test_panel);

	ASSERT_TRUE(panel_manager.in_const_panels({0, 0}));
}

TEST(PanelManager, update_interactions) {
	TestPanel test_panel{false, {0, 0}, {100, 100}, true, true, true, false};
	TestPanel test_panel1{};
	ie::PanelManager panel_manager{};
	panel_manager.display_panel(&test_panel1);
	panel_manager.display_panel(&test_panel);

	panel_manager.update_interactions({5, 5}, true);

	ASSERT_GT(test_panel.get_processed().update_interactions_with_active.time, 0);
	ASSERT_GT(test_panel1.get_processed().update_interactions_with_active.time, 0);
	ASSERT_GT(test_panel1.get_processed().update_interactions_with_active.time, test_panel.get_processed().update_interactions_with_active.time);

	ASSERT_TRUE((test_panel.get_processed().update_interactions_with_active.mouse_position == sf::Vector2f{5, 5}));
	ASSERT_TRUE(test_panel.get_processed().update_interactions_with_active.active);

	ASSERT_TRUE((test_panel1.get_processed().update_interactions_with_active.mouse_position == sf::Vector2f{5, 5}));
	ASSERT_TRUE(test_panel1.get_processed().update_interactions_with_active.active);

	panel_manager.update_interactions({6, 6}, true);

	ASSERT_GT(test_panel.get_processed().update_interactions_with_active.time, 0);
	ASSERT_GT(test_panel1.get_processed().update_interactions_with_active.time, 0);
	ASSERT_GT(test_panel.get_processed().update_interactions_with_active.time, test_panel1.get_processed().update_interactions_with_active.time);

	ASSERT_TRUE((test_panel1.get_processed().update_interactions_with_active.mouse_position == sf::Vector2f{6, 6}));
	ASSERT_TRUE(test_panel1.get_processed().update_interactions_with_active.active);

	ASSERT_TRUE((test_panel.get_processed().update_interactions_with_active.mouse_position == sf::Vector2f{6, 6}));
	ASSERT_FALSE(test_panel.get_processed().update_interactions_with_active.active);
}