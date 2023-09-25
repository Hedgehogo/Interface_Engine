#include "testPanel.hpp"
#include "../../../lib/IE/IComponent/IScalable/IUninteractive/OnlyDrawable/Empty/Empty.hpp"

#include "../processorTime.hpp"

TestPanel::Make::Make(
	bool displayed,
	sf::Vector2f minSize,
	sf::Vector2f normalSize,
	bool isIndependentResult,
	bool isFreeResult,
	bool inPanelResult,
	bool updateInteractionsResult,
	ie::BoxPtr<ie::ISizing2> sizing,
	ie::BoxPtr<ie::IPositioning2> positioning
) :
	displayed(displayed),
	minSize(minSize),
	normalSize(normalSize),
	isIndependentResult(isIndependentResult),
	isFreeResult(isFreeResult),
	inPanelResult(inPanelResult),
	updateInteractionsResult(updateInteractionsResult),
	sizing(std::move(sizing)),
	positioning(std::move(positioning)) {
}

TestPanel* TestPanel::Make::make(ie::InitInfo initInfo) {
	return new TestPanel{std::move(*this), initInfo};
}

TestPanel::TestPanel(Make&& make, ie::InitInfo initInfo) :
	BasePanel(
		ie::BoxPtr < ie::IScalable::Make > {new ie::Empty::Make{}},
		std::move(make.sizing),
		std::move(make.positioning),
		make.displayed,
		initInfo,
		initInfo
	),
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
	minSize(make.minSize),
	normalSize(make.normalSize),
	isIndependentResult(make.isIndependentResult),
	isFreeResult(make.isFreeResult),
	inPanelResult(make.inPanelResult),
	updateInteractionsResult(make.updateInteractionsResult) {
}

TestPanel::TestPanel(
	bool displayed,
	sf::Vector2f minSize,
	sf::Vector2f normalSize,
	bool isIndependentResult,
	bool isFreeResult,
	bool inPanelResult,
	bool updateInteractionsResult,
	ie::BoxPtr<ie::ISizing2> sizing,
	ie::BoxPtr<ie::IPositioning2> positioning
) : BasePanel(ie::BoxPtr < ie::IScalable > {new ie::Empty{}}, std::move(sizing), std::move(positioning), displayed), minSize(minSize), normalSize(normalSize),
	isIndependentResult(isIndependentResult), isFreeResult(isFreeResult), inPanelResult(inPanelResult), updateInteractionsResult(updateInteractionsResult) {
}

const TestPanel::Processed& TestPanel::getProcessed() const {
	return processed;
}

void TestPanel::init(ie::InitInfo initInfo) {
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
