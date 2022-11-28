#include "testPanel.hpp"
#include "../../../lib/ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/empty/empty.hpp"

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

TestPanel::TestPanel(bool displayed, const sf::Vector2f &minSize, const sf::Vector2f &normalSize, bool isIndependentResult, bool isFreeResult, bool inPanelResult, bool updateInteractionsResult, ui::ISizing2 *sizing,
                     ui::IPositioning2 *positioning) :
					 BasePanel(new ui::Empty{}, sizing, positioning, displayed), minSize(minSize), normalSize(normalSize),
                     isIndependentResult(isIndependentResult), isFreeResult(isFreeResult), inPanelResult(inPanelResult),updateInteractionsResult(updateInteractionsResult) {}

const TestPanel::Processed &TestPanel::getProcessed() const {
	return processed;
}

void TestPanel::init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) {
	BasePanel::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);

	processed.init.time = __rdtsc();
	processed.init.renderTarget = &renderTarget;
	processed.init.drawManager = &drawManager;
	processed.init.updateManager = &updateManager;
	processed.init.interactionManager = &interactionManager;
	processed.init.interactionStack = &interactionStack;
	processed.init.panelManager = &panelManager;
}

bool TestPanel::isIndependent() {
	return isIndependentResult;
}

bool TestPanel::isFree() {
	return isFreeResult;
}

void TestPanel::setDisplayed() {
	BasePanel::setDisplayed();
	processed.setDisplayed = __rdtsc();
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
	processed.draw = __rdtsc();
}

void TestPanel::resize(sf::Vector2f size, sf::Vector2f position) {
	BasePanel::resize(size, position);
}

void TestPanel::update() {
	processed.update = __rdtsc();
}

bool TestPanel::updateInteractions(sf::Vector2f mousePosition) {
	BasePanel::updateInteractions(mousePosition);
	processed.updateInteractions.time = __rdtsc();
	processed.updateInteractions.mousePosition = mousePosition;
	return updateInteractionsResult;
}

bool TestPanel::updateInteractions(sf::Vector2f mousePosition, bool active) {
	BasePanel::updateInteractions(mousePosition, active);
	processed.updateInteractionsWithActive.time = __rdtsc();
	processed.updateInteractionsWithActive.mousePosition = mousePosition;
	processed.updateInteractionsWithActive.active = active;
	return updateInteractionsResult;
}

sf::Vector2f TestPanel::getMinSize() {
	return minSize;
}

sf::Vector2f TestPanel::getNormalSize() {
	return normalSize;
}

TestPanel *TestPanel::copy() {
	return new TestPanel{displayed, minSize, normalSize, isIndependentResult, isFreeResult, inPanelResult, updateInteractionsResult, sizing->copy(), positioning->copy()};
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

