#include <gtest/gtest.h>

#include "../../../testsObjects/testInteraction/testInteraction.hpp"
#include "../../../../lib/ui/interaction/interactionManager/interactionManager.hpp"

void testStart(TestInteraction& testInteraction, TestInteraction& testInteraction1, ui::InteractionManager& interactionManager){
	ASSERT_EQ(testInteraction.getProcessed().start.size(), 1);
	ASSERT_TRUE(testInteraction.getProcessed().start[0].mousePosition == (sf::Vector2i{3, 3}));

	ASSERT_EQ(testInteraction1.getProcessed().start.size(), 1);
	ASSERT_TRUE(testInteraction1.getProcessed().start[0].mousePosition == (sf::Vector2i{3, 3}));


	ASSERT_EQ(testInteraction.getProcessed().update.size(), 1);
	ASSERT_GT(testInteraction.getProcessed().update[0].time, testInteraction.getProcessed().start[0].time);
	ASSERT_TRUE(testInteraction.getProcessed().update[0].mousePosition == (sf::Vector2i{3, 3}));

	ASSERT_EQ(testInteraction1.getProcessed().update.size(), 1);
	ASSERT_GT(testInteraction1.getProcessed().update[0].time, testInteraction.getProcessed().start[0].time);
	ASSERT_TRUE(testInteraction1.getProcessed().update[0].mousePosition == (sf::Vector2i{3, 3}));
}

void testUpdate(TestInteraction& testInteraction, TestInteraction& testInteraction1, ui::InteractionManager& interactionManager){
	ASSERT_EQ(testInteraction.getProcessed().update.size(), 2);
	ASSERT_GT(testInteraction.getProcessed().update[1].time, testInteraction.getProcessed().update[0].time);
	ASSERT_TRUE(testInteraction.getProcessed().update[1].mousePosition == (sf::Vector2i{2, 2}));

	ASSERT_EQ(testInteraction1.getProcessed().update.size(), 2);
	ASSERT_GT(testInteraction1.getProcessed().update[1].time, testInteraction1.getProcessed().update[0].time);
	ASSERT_TRUE(testInteraction1.getProcessed().update[1].mousePosition == (sf::Vector2i{2, 2}));
}

TEST(InteractionManager, update_and_add) {
	TestInteraction testInteraction{};
	TestInteraction testInteraction1{};

	ui::InteractionManager interactionManager{};

	interactionManager.addInteraction(testInteraction);
	interactionManager.addInteraction(testInteraction1);

	interactionManager.update({3, 3});

	testStart(testInteraction, testInteraction1, interactionManager);

	interactionManager.update({2, 2});

	testUpdate(testInteraction, testInteraction1, interactionManager);
}

TEST(InteractionManager, add_delete) {
	TestInteraction testInteraction{};
	TestInteraction testInteraction1{};

	ui::InteractionManager interactionManager{};
	interactionManager.addInteraction(testInteraction);
	interactionManager.addInteraction(testInteraction1);

	interactionManager.update({3, 3});
	interactionManager.update({2, 2});
	interactionManager.deleteInteraction(testInteraction1);
	interactionManager.update({1, 1});

	ASSERT_EQ(testInteraction.getProcessed().update.size(), 3);
	ASSERT_EQ(testInteraction1.getProcessed().update.size(), 2);
	ASSERT_EQ(testInteraction1.getProcessed().finish.size(), 1);
	ASSERT_GT(testInteraction.getProcessed().update[2].time, testInteraction1.getProcessed().finish[0].time);
	ASSERT_GT(testInteraction1.getProcessed().finish[0].time, testInteraction1.getProcessed().update[1].time);
}

TEST(InteractionManager, clear) {

	TestInteraction testInteraction{};
	TestInteraction testInteraction1{};

	ui::InteractionManager interactionManager{};
	interactionManager.addInteraction(testInteraction);
	interactionManager.addInteraction(testInteraction1);

	interactionManager.update({3, 3});
	interactionManager.clear();
	interactionManager.update({2, 2});

	ASSERT_EQ(testInteraction.getProcessed().update.size(), 1);
	ASSERT_TRUE(testInteraction.getProcessed().update[0].mousePosition == (sf::Vector2i{3, 3}));
	ASSERT_EQ(testInteraction1.getProcessed().update.size(), 1);
	ASSERT_TRUE(testInteraction.getProcessed().update[0].mousePosition == (sf::Vector2i{3, 3}));
}

TEST(InteractionManager, isBlocked) {
	TestInteraction testInteraction{};
	TestInteraction testInteraction1{};

	ui::InteractionManager interactionManager{};
	interactionManager.addInteraction(testInteraction);
	interactionManager.addInteraction(testInteraction1);

	interactionManager.update({3, 3});

	ASSERT_FALSE(interactionManager.isBlocked());

	TestInteraction testInteraction2{ui::IInteraction::Priority::medium, true};
	interactionManager.addInteraction(testInteraction2);
	interactionManager.update({2, 2});

	ASSERT_TRUE(interactionManager.isBlocked());
}

TEST(InteractionManager, priority) {
	TestInteraction testInteraction{ui::IInteraction::Priority::highest},
					testInteraction1{ui::IInteraction::Priority::medium},
					testInteraction2{ui::IInteraction::Priority::lowest};

	ui::InteractionManager interactionManager{};
	interactionManager.addInteraction(testInteraction2);
	interactionManager.addInteraction(testInteraction1);
	interactionManager.addInteraction(testInteraction);

	interactionManager.update({3, 3});

	ASSERT_LT(testInteraction.getProcessed().update[0].time, testInteraction1.getProcessed().update[0].time);
	ASSERT_LT(testInteraction1.getProcessed().update[0].time, testInteraction2.getProcessed().update[0].time);
}
