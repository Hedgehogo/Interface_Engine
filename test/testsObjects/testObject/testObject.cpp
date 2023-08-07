#include "testObject.hpp"

#include "../processorTime.hpp"

TestObject::Make::Make(sf::Vector2f minSize, sf::Vector2f normalSize, bool updateInteractionsResult) :
	minSize(minSize), normalSize(normalSize), updateInteractionsResult(updateInteractionsResult) {
}

TestObject* TestObject::Make::make(ui::InitInfo initInfo) {
	return new TestObject{std::move(*this), initInfo};
}

TestObject::TestObject(TestObject::Make&& make, ui::InitInfo initInfo) :
	processed(
		{
			{
				getProcessorTime(),
				&initInfo.renderTarget,
				&initInfo.drawManager,
				&initInfo.updateManager,
				&initInfo.interactionManager,
				&initInfo.interactionStack,
				&initInfo.panelManager
			}
		}
	),
	updateInteractionsResult(make.updateInteractionsResult),
	minSize(make.minSize),
	normalSize(make.normalSize) {
	initInfo.drawManager.add(*this);
	initInfo.updateManager.add(*this);
}

TestObject::TestObject(sf::Vector2f minSize, sf::Vector2f normalSize, bool updateInteractionsResult) :
	updateInteractionsResult(updateInteractionsResult), minSize(minSize), normalSize(normalSize) {
}

void TestObject::init(ui::InitInfo initInfo) {
	processed.init.time = getProcessorTime();
	processed.init.renderTarget = &initInfo.renderTarget;
	processed.init.drawManager = &initInfo.drawManager;
	processed.init.updateManager = &initInfo.updateManager;
	processed.init.interactionManager = &initInfo.interactionManager;
	processed.init.interactionStack = &initInfo.interactionStack;
	processed.init.panelManager = &initInfo.panelManager;
	
	initInfo.drawManager.add(*this);
	initInfo.updateManager.add(*this);
}

TestObject::Processed TestObject::getProcessed() {
	return processed;
}

sf::Vector2f TestObject::getMinSize() const {
	return minSize;
}

sf::Vector2f TestObject::getNormalSize() const {
	return normalSize;
}

ui::LayoutData& TestObject::getLayoutData() {
	return layoutData;
}

const ui::LayoutData& TestObject::getLayoutData() const {
	return layoutData;
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

TestObject* TestObject::copy() {
	processed.copy = getProcessorTime();
	return new TestObject{*this};
}

void TestObject::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
	processed.drawDebug = getProcessorTime();
}
