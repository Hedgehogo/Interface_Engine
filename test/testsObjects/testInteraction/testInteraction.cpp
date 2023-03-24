#include "testInteraction.hpp"

#include "../processorTime.hpp"

TestInteraction::TestInteraction(Priority priority, bool blocked) :
	priority(priority), IInteraction(), blocked(blocked) {}

TestInteraction::Processed TestInteraction::getProcessed() {
	return processed;
}

ui::IInteraction::Priority TestInteraction::getPriority() const {
	return priority;
}

bool TestInteraction::isBlocked() const {
	return blocked;
}

void TestInteraction::start(sf::Vector2i mousePosition) {
	processed.start.push_back({getProcessorTime(), mousePosition});
}

void TestInteraction::update(sf::Vector2i mousePosition) {
	processed.update.push_back({getProcessorTime(), mousePosition});
}

void TestInteraction::finish(sf::Vector2i mousePosition) {
	processed.finish.push_back({getProcessorTime(), mousePosition});
}

ui::IInteraction *TestInteraction::copy() {
	processed.copy.push_back(getProcessorTime());
	return new TestInteraction{priority, blocked};
}
