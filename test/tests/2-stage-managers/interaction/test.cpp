#include <gtest/gtest.h>

#include "../../../tests_objects/test_interaction/test_interaction.hpp"
#include "../../../../lib/IE/Interaction/InteractionManager/InteractionManager.hpp"

void test_start(TestInteraction& test_interaction, TestInteraction& test_interaction1, ie::InteractionManager& interaction_manager){
	ASSERT_EQ(test_interaction.get_processed().start.size(), 1);
	ASSERT_TRUE(test_interaction.get_processed().start[0].mouse_position == (sf::Vector2i{3, 3}));

	ASSERT_EQ(test_interaction1.get_processed().start.size(), 1);
	ASSERT_TRUE(test_interaction1.get_processed().start[0].mouse_position == (sf::Vector2i{3, 3}));


	ASSERT_EQ(test_interaction.get_processed().update.size(), 1);
	ASSERT_GT(test_interaction.get_processed().update[0].time, test_interaction.get_processed().start[0].time);
	ASSERT_TRUE(test_interaction.get_processed().update[0].mouse_position == (sf::Vector2i{3, 3}));

	ASSERT_EQ(test_interaction1.get_processed().update.size(), 1);
	ASSERT_GT(test_interaction1.get_processed().update[0].time, test_interaction.get_processed().start[0].time);
	ASSERT_TRUE(test_interaction1.get_processed().update[0].mouse_position == (sf::Vector2i{3, 3}));
}

void test_update(TestInteraction& test_interaction, TestInteraction& test_interaction1, ie::InteractionManager& interaction_manager){
	ASSERT_EQ(test_interaction.get_processed().update.size(), 2);
	ASSERT_GT(test_interaction.get_processed().update[1].time, test_interaction.get_processed().update[0].time);
	ASSERT_TRUE(test_interaction.get_processed().update[1].mouse_position == (sf::Vector2i{2, 2}));

	ASSERT_EQ(test_interaction1.get_processed().update.size(), 2);
	ASSERT_GT(test_interaction1.get_processed().update[1].time, test_interaction1.get_processed().update[0].time);
	ASSERT_TRUE(test_interaction1.get_processed().update[1].mouse_position == (sf::Vector2i{2, 2}));
}

TEST(InteractionManager, update_and_add) {
	TestInteraction test_interaction{};
	TestInteraction test_interaction1{};

	ie::InteractionManager interaction_manager{};

	interaction_manager.add_interaction(test_interaction);
	interaction_manager.add_interaction(test_interaction1);

	interaction_manager.update({3, 3});

	test_start(test_interaction, test_interaction1, interaction_manager);

	interaction_manager.update({2, 2});

	test_update(test_interaction, test_interaction1, interaction_manager);
}

TEST(InteractionManager, add_delete) {
	TestInteraction test_interaction{};
	TestInteraction test_interaction1{};

	ie::InteractionManager interaction_manager{};
	interaction_manager.add_interaction(test_interaction);
	interaction_manager.add_interaction(test_interaction1);

	interaction_manager.update({3, 3});
	interaction_manager.update({2, 2});
	interaction_manager.delete_interaction(test_interaction1);
	interaction_manager.update({1, 1});

	ASSERT_EQ(test_interaction.get_processed().update.size(), 3);
	ASSERT_EQ(test_interaction1.get_processed().update.size(), 2);
	ASSERT_EQ(test_interaction1.get_processed().finish.size(), 1);
	ASSERT_GT(test_interaction.get_processed().update[2].time, test_interaction1.get_processed().finish[0].time);
	ASSERT_GT(test_interaction1.get_processed().finish[0].time, test_interaction1.get_processed().update[1].time);
}

TEST(InteractionManager, clear) {

	TestInteraction test_interaction{};
	TestInteraction test_interaction1{};

	ie::InteractionManager interaction_manager{};
	interaction_manager.add_interaction(test_interaction);
	interaction_manager.add_interaction(test_interaction1);

	interaction_manager.update({3, 3});
	interaction_manager.clear();
	interaction_manager.update({2, 2});

	ASSERT_EQ(test_interaction.get_processed().update.size(), 1);
	ASSERT_TRUE(test_interaction.get_processed().update[0].mouse_position == (sf::Vector2i{3, 3}));
	ASSERT_EQ(test_interaction1.get_processed().update.size(), 1);
	ASSERT_TRUE(test_interaction.get_processed().update[0].mouse_position == (sf::Vector2i{3, 3}));
}

TEST(InteractionManager, is_blocked) {
	TestInteraction test_interaction{};
	TestInteraction test_interaction1{};

	ie::InteractionManager interaction_manager{};
	interaction_manager.add_interaction(test_interaction);
	interaction_manager.add_interaction(test_interaction1);

	interaction_manager.update({3, 3});

	ASSERT_FALSE(interaction_manager.is_blocked());

	TestInteraction test_interaction2{ie::IInteraction::Priority::medium, true};
	interaction_manager.add_interaction(test_interaction2);
	interaction_manager.update({2, 2});

	ASSERT_TRUE(interaction_manager.is_blocked());
}

TEST(InteractionManager, priority) {
	TestInteraction test_interaction{ie::IInteraction::Priority::highest},
					test_interaction1{ie::IInteraction::Priority::medium},
					test_interaction2{ie::IInteraction::Priority::lowest};

	ie::InteractionManager interaction_manager{};
	interaction_manager.add_interaction(test_interaction2);
	interaction_manager.add_interaction(test_interaction1);
	interaction_manager.add_interaction(test_interaction);

	interaction_manager.update({3, 3});

	ASSERT_LT(test_interaction.get_processed().update[0].time, test_interaction1.get_processed().update[0].time);
	ASSERT_LT(test_interaction1.get_processed().update[0].time, test_interaction2.get_processed().update[0].time);
}
