#include "testObject.hpp"

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

TestObject::TestObject(sf::Vector2f minSize, sf::Vector2f normalSize, bool updateInteractionsResult) : minSize(minSize), normalSize(normalSize), updateInteractionsResult(updateInteractionsResult) {}

void TestObject::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
	processed.init.time = __rdtsc();
	processed.init.renderTarget = &renderTarget;
	processed.init.drawManager = &drawManager;
	processed.init.updateManager = &updateManager;
	processed.init.interactionManager = &interactionManager;
	processed.init.interactionStack = &interactionStack;
	processed.init.panelManager = &panelManager;

	drawManager.add(*this);
	updateManager.add(*this);
}

TestObject::Processed TestObject::getProcessed() {
	return processed;
}

sf::Vector2f TestObject::getMinSize() {
	return minSize;
}

sf::Vector2f TestObject::getNormalSize() {
	return normalSize;
}

bool TestObject::updateInteractions(sf::Vector2f mousePosition) {
	processed.updateInteractions.time = __rdtsc();
	processed.updateInteractions.mousePosition = mousePosition;
	return updateInteractionsResult;
}

void TestObject::draw() {
	processed.draw = __rdtsc();
}

void TestObject::update() {
	processed.update = __rdtsc();
}

TestObject *TestObject::copy() {
	processed.copy = __rdtsc();
	return new TestObject{minSize, normalSize, updateInteractionsResult};
}

void TestObject::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
	processed.drawDebug = __rdtsc();
}
