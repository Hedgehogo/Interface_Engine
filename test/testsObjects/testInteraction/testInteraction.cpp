#include "testInteraction.hpp"

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

TestInteraction::TestInteraction(Priority priority, bool blocked) :
	ui::IInteraction(), priority(priority), testInteraction(testInteraction), IInteraction() {}

TestInteraction::Processed TestInteraction::getProcessed() {
	return processed;
}

void TestInteraction::start(sf::Vector2i mousePosition) {
	processed.start.push_back({__rdtsc(), mousePosition});
}

void TestInteraction::update(sf::Vector2i mousePosition) {
	processed.update.push_back({__rdtsc(), mousePosition});
	return updateResult;
}

void TestInteraction::finish(sf::Vector2i mousePosition) {
	processed.finish.push_back({__rdtsc(), mousePosition});
}

ui::IInteraction *TestInteraction::copy() {
	processed.copy.push_back(__rdtsc());
	return new TestInteraction{priority, blocked};
}