#include "basePanel.hpp"
#include "../manager/general/panelManager.hpp"

namespace ui {
	BasePanel::BasePanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed) :
		object(std::move(object)), sizing(std::move(sizing)), positioning(std::move(positioning)),
		displayed(displayed), oldDisplayed(false), parentProcessed(false), active(false) {
	}
	
	BasePanel::BasePanel(const BasePanel& other) :
		layout(other.layout), object(other.object), sizing(other.sizing), positioning(other.positioning),
		displayed(other.displayed), oldDisplayed(other.oldDisplayed), parentProcessed(other.parentProcessed), active(false) {
	}
	
	void BasePanel::init(InitInfo initInfo) {
		initInfo.panelManager.addPanel(this);
		sf::Vector2f objectNormalSize = object->getNormalSize();
		sizing->init(initInfo.renderTarget, objectNormalSize);
		positioning->init(initInfo.renderTarget);
	}
	
	void BasePanel::setDisplayed() {
	}
	
	void BasePanel::setParentProcessed(bool parentProcessed) {
		this->parentProcessed = parentProcessed;
	}
	
	bool BasePanel::getParentProcessed() {
		return this->parentProcessed;
	}
	
	bool BasePanel::inPanel(sf::Vector2f pointPosition) {
		return active && ILayout::inArea(pointPosition);
	}
	
	void BasePanel::setPosition(sf::Vector2f position) {
		ILayout::resize(layout.size, position);
		object->setPosition(position);
	}
	
	void BasePanel::move(sf::Vector2f position) {
		ILayout::resize(layout.size, layout.position + position);
		object->move(position);
	}
	
	void BasePanel::setSize(sf::Vector2f size) {
		ILayout::resize(size, layout.position);
		object->setSize(size);
	}
	
	void BasePanel::draw() {
		drawManager.draw();
	}
	
	void BasePanel::resize(sf::Vector2f size, sf::Vector2f position) {
		sf::Vector2f panelSize = (*sizing)(size);
		sf::Vector2f panelPosition = (*positioning)(position, size, panelSize);
		ILayoutWithObject::resize(panelSize, panelPosition);
	}
	
	void BasePanel::update() {
		oldDisplayed = displayed;
		displayed = false;
		updateManager.update();
	}
	
	bool BasePanel::updateInteractions(sf::Vector2f mousePosition) {
		return inPanel(mousePosition) && object->updateInteractions(mousePosition);
	}
	
	bool BasePanel::updateInteractions(sf::Vector2f mousePosition, bool active) {
		displayed = true;
		this->active = active;
		return updateInteractions(mousePosition);
	}
	
	sf::Vector2f BasePanel::getMinSize() const {
		return sizing->getParentSize(object->getMinSize());
	}
	
	sf::Vector2f BasePanel::getNormalSize() const {
		return sizing->getParentSize(object->getNormalSize());
	}
	
	LayoutData& BasePanel::getLayoutData() {
		return layout;
	}
	
	const LayoutData& BasePanel::getLayoutData() const {
		return layout;
	}
	
	IScalable& BasePanel::getObject() {
		return *object;
	}
	
	const IScalable& BasePanel::getObject() const {
		return *object;
	}
	
	bool BasePanel::fullDebug = false;
	
	void BasePanel::setFullDebug(bool fullDebug) {
		BasePanel::fullDebug = fullDebug;
	}
	
	void BasePanel::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		if(fullDebug || oldDisplayed) {
			object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		}
	}
}