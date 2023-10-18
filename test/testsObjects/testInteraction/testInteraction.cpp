#include "test_interaction.hpp"

#include "../processor_time.hpp"

TestInteraction::TestInteraction(Priority priority, bool blocked) :
	priority(priority), IInteraction(), blocked(blocked) {}

TestInteraction::Processed TestInteraction::get_processed() {
	return processed;
}

ie::IInteraction::Priority TestInteraction::get_priority() const {
	return priority;
}

bool TestInteraction::is_blocked() const {
	return blocked;
}

void TestInteraction::start(sf::Vector2i mouse_position) {
	processed.start.push_back({get_processor_time(), mouse_position});
}

void TestInteraction::update(sf::Vector2i mouse_position) {
	processed.update.push_back({get_processor_time(), mouse_position});
}

void TestInteraction::finish(sf::Vector2i mouse_position) {
	processed.finish.push_back({get_processor_time(), mouse_position});
}

ie::IInteraction *TestInteraction::copy() {
	processed.copy.push_back(get_processor_time());
	return new TestInteraction{priority, blocked};
}
