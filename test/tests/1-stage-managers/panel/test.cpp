#include "../../../createTestProgram/createTestProgram.hpp"
#include "../../../testsObjects/testPanel/testPanel.hpp"

TEST(PanelManager, draw_and_displayPanel) {
	TestPanel testPanel{};
	ui::PanelManager panelManager{{&testPanel}};
	panelManager.displayPanel(&testPanel);

	panelManager.draw();

	ASSERT_GT(testPanel.getProcessed().draw, 0);
}

TEST(PanelManager, draw_and_hidePanel) {
	TestPanel testPanel{};
	ui::PanelManager panelManager{};
	panelManager.displayPanel(&testPanel);
	panelManager.hidePanel(&testPanel);

	panelManager.draw();

	ASSERT_EQ(testPanel.getProcessed().draw, 0);
}

TEST(PanelManager, update_and_addPanel) {
	TestPanel testPanel{};
	ui::PanelManager panelManager{};
	panelManager.addPanel(&testPanel);

	panelManager.update();

	ASSERT_GT(testPanel.getProcessed().update, 0);
}

TEST(PanelManager, update_and_removePanel) {
	TestPanel testPanel{};
	ui::PanelManager panelManager{};
	panelManager.addPanel(&testPanel);
	panelManager.removePanel(&testPanel);

	panelManager.update();

	ASSERT_EQ(testPanel.getProcessed().update, 0);
}

TEST(PanelManager, isFree) {
	TestPanel testPanelNotFree{false, {0, 0}, {100, 100}, false};
	TestPanel testPanelNotFree1{false, {0, 0}, {100, 100}, false};
	ui::PanelManager panelManager{{&testPanelNotFree, &testPanelNotFree1}};
	panelManager.displayPanel(&testPanelNotFree);
	panelManager.displayPanel(&testPanelNotFree1);
	ASSERT_TRUE(panelManager.isFree());

	TestPanel testPanel{};

	panelManager.displayPanel(&testPanel);

	ASSERT_FALSE(panelManager.isFree());
}

TEST(PanelManager, inConstPanels) {
	TestPanel testPanelNotFree{};
	TestPanel testPanelNotFree1{};
	ui::PanelManager panelManager{{&testPanelNotFree, &testPanelNotFree1}};
	panelManager.displayPanel(&testPanelNotFree);
	panelManager.displayPanel(&testPanelNotFree1);
	ASSERT_FALSE(panelManager.inConstPanels({0, 0}));

	TestPanel testPanel{false, {0, 0}, {100, 100}, false};

	panelManager.displayPanel(&testPanel);

	ASSERT_TRUE(panelManager.inConstPanels({0, 0}));
}

TEST(PanelManager, updateInteractions) {
	TestPanel testPanel{false, {0, 0}, {100, 100}, true, true, true, false};
	TestPanel testPanel1{};
	ui::PanelManager panelManager{};
	panelManager.displayPanel(&testPanel1);
	panelManager.displayPanel(&testPanel);

	panelManager.updateInteractions({5, 5}, true);

	ASSERT_GT(testPanel.getProcessed().updateInteractionsWithActive.time, 0);
	ASSERT_GT(testPanel1.getProcessed().updateInteractionsWithActive.time, 0);
	ASSERT_GT(testPanel1.getProcessed().updateInteractionsWithActive.time, testPanel.getProcessed().updateInteractionsWithActive.time);

	ASSERT_TRUE((testPanel.getProcessed().updateInteractionsWithActive.mousePosition == sf::Vector2f{5, 5}));
	ASSERT_TRUE(testPanel.getProcessed().updateInteractionsWithActive.active);

	ASSERT_TRUE((testPanel1.getProcessed().updateInteractionsWithActive.mousePosition == sf::Vector2f{5, 5}));
	ASSERT_TRUE(testPanel1.getProcessed().updateInteractionsWithActive.active);

	panelManager.updateInteractions({6, 6}, true);

	ASSERT_GT(testPanel.getProcessed().updateInteractionsWithActive.time, 0);
	ASSERT_GT(testPanel1.getProcessed().updateInteractionsWithActive.time, 0);
	ASSERT_GT(testPanel.getProcessed().updateInteractionsWithActive.time, testPanel1.getProcessed().updateInteractionsWithActive.time);

	ASSERT_TRUE((testPanel1.getProcessed().updateInteractionsWithActive.mousePosition == sf::Vector2f{6, 6}));
	ASSERT_TRUE(testPanel1.getProcessed().updateInteractionsWithActive.active);

	ASSERT_TRUE((testPanel.getProcessed().updateInteractionsWithActive.mousePosition == sf::Vector2f{6, 6}));
	ASSERT_FALSE(testPanel.getProcessed().updateInteractionsWithActive.active);
}