#include "testInteraction.hpp"

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

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
	processed.start.push_back({__rdtsc(), mousePosition});
}

void TestInteraction::update(sf::Vector2i mousePosition) {
	processed.update.push_back({__rdtsc(), mousePosition});
}

void TestInteraction::finish(sf::Vector2i mousePosition) {
	processed.finish.push_back({__rdtsc(), mousePosition});
}

ui::IInteraction *TestInteraction::copy() {
	processed.copy.push_back(__rdtsc());
	return new TestInteraction{priority, blocked};
}
