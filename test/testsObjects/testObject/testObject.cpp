#include "testObject.hpp"

#include "../processorTime.hpp"

TestObject::TestObject(sf::Vector2f minSize, sf::Vector2f normalSize, bool updateInteractionsResult) : minSize(minSize), normalSize(normalSize), updateInteractionsResult(updateInteractionsResult) {}

void TestObject::init(ui::InitInfo initInfo) {
	processed.init.time = getProcessorTime();
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
	processed.updateInteractions.time = getProcessorTime();
	processed.updateInteractions.mousePosition = mousePosition;
	return updateInteractionsResult;
}

void TestObject::draw() {
	processed.draw = getProcessorTime();
}

void TestObject::update() {
	processed.update = getProcessorTime();
}

TestObject *TestObject::copy() {
	processed.copy = getProcessorTime();
	return new TestObject{minSize, normalSize, updateInteractionsResult};
}

void TestObject::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
	processed.drawDebug = getProcessorTime();
}
