#include "testPanel.hpp"
#include "../../../lib/ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/empty/empty.hpp"

#include "../processorTime.hpp"

TestPanel::TestPanel(
	bool displayed,
	const sf::Vector2f& minSize,
	const sf::Vector2f& normalSize,
	bool isIndependentResult,
	bool isFreeResult,
	bool inPanelResult,
	bool updateInteractionsResult,
	ui::BoxPtr<ui::ISizing2> sizing,
	ui::BoxPtr<ui::IPositioning2> positioning
) : BasePanel(ui::BoxPtr<ui::IScalable>{new ui::Empty{}}, std::move(sizing), std::move(positioning), displayed), minSize(minSize), normalSize(normalSize),
	isIndependentResult(isIndependentResult), isFreeResult(isFreeResult), inPanelResult(inPanelResult), updateInteractionsResult(updateInteractionsResult) {
}

const TestPanel::Processed& TestPanel::getProcessed() const {
	return processed;
}

void TestPanel::init(ui::InitInfo initInfo) {
	BasePanel::init(initInfo);
	
	processed.init.time = getProcessorTime();
	processed.init.renderTarget = &initInfo.renderTarget;
	processed.init.drawManager = &initInfo.drawManager;
	processed.init.updateManager = &initInfo.updateManager;
	processed.init.interactionManager = &initInfo.interactionManager;
	processed.init.interactionStack = &initInfo.interactionStack;
	processed.init.panelManager = &initInfo.panelManager;
}

bool TestPanel::isIndependent() {
	return isIndependentResult;
}

bool TestPanel::isFree() {
	return isFreeResult;
}

void TestPanel::setDisplayed() {
	BasePanel::setDisplayed();
	processed.setDisplayed = getProcessorTime();
}

void TestPanel::setParentProcessed(bool parentProcessed) {
	BasePanel::setParentProcessed(parentProcessed);
}

bool TestPanel::getParentProcessed() {
	return BasePanel::getParentProcessed();
}

bool TestPanel::inPanel(sf::Vector2f pointPosition) {
	return inPanelResult;
}

void TestPanel::setPosition(sf::Vector2f position) {
	BasePanel::setPosition(position);
}

void TestPanel::move(sf::Vector2f position) {
	BasePanel::move(position);
}

void TestPanel::setSize(sf::Vector2f size) {
	BasePanel::setSize(size);
}

void TestPanel::draw() {
	processed.draw = getProcessorTime();
}

void TestPanel::resize(sf::Vector2f size, sf::Vector2f position) {
	BasePanel::resize(size, position);
}

void TestPanel::update() {
	processed.update = getProcessorTime();
}

bool TestPanel::updateInteractions(sf::Vector2f mousePosition) {
	BasePanel::updateInteractions(mousePosition);
	processed.updateInteractions.time = getProcessorTime();
	processed.updateInteractions.mousePosition = mousePosition;
	return updateInteractionsResult;
}

bool TestPanel::updateInteractions(sf::Vector2f mousePosition, bool active) {
	BasePanel::updateInteractions(mousePosition, active);
	processed.updateInteractionsWithActive.time = getProcessorTime();
	processed.updateInteractionsWithActive.mousePosition = mousePosition;
	processed.updateInteractionsWithActive.active = active;
	return updateInteractionsResult;
}

sf::Vector2f TestPanel::getMinSize() const {
	return minSize;
}

sf::Vector2f TestPanel::getNormalSize() const {
	return normalSize;
}

TestPanel* TestPanel::copy() {
	return new TestPanel{*this};
}

void TestPanel::setIsIndependentResult(bool isIndependentResult) {
	TestPanel::isIndependentResult = isIndependentResult;
}

void TestPanel::setIsFreeResult(bool isFreeResult) {
	TestPanel::isFreeResult = isFreeResult;
}

void TestPanel::setInPanelResult(bool inPanelResult) {
	TestPanel::inPanelResult = inPanelResult;
}

void TestPanel::setUpdateInteractionsResult(bool updateInteractionsResult) {
	TestPanel::updateInteractionsResult = updateInteractionsResult;
}

