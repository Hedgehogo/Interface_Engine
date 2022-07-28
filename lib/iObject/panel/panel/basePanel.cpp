#include "basePanel.h"
#include "../manager/panelManager.h"
#include "../../../drawable/manager/drawManager.h"

namespace ui {
	BasePanel::BasePanel(IScalable *object, Sizing2 *sizing, Positioning2 *positioning, bool displayed) :
		LayoutWithObject(object), sizing(sizing), positioning(positioning),
		displayed(displayed), oldDisplayed(false), parentProcessed(false), active(false) {}
	
	void BasePanel::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		panelManager.addPanel(this);
		sf::Vector2f objectNormalSize = object->getNormalSize();
		sizing->init(renderTarget, objectNormalSize);
		positioning->init(renderTarget);
	}
	
	BasePanel::~BasePanel() {
		delete sizing;
		delete positioning;
	}
	
	void BasePanel::setDisplayed() {}
	
	void BasePanel::setParentProcessed(bool parentProcessed) {
		this->parentProcessed = parentProcessed;
	}
	
	bool BasePanel::getParentProcessed() {
		return this->parentProcessed;
	}
	
	bool BasePanel::inPanel(sf::Vector2f pointPosition) {
		return active && Layout::inArea(pointPosition);
	}
	
	void BasePanel::setPosition(sf::Vector2f position) {
		Layout::resize(this->size, position);
		object->setPosition(position);
	}
	
	void BasePanel::move(sf::Vector2f position) {
		Layout::resize(this->size, this->position + position);
		object->move(position);
	}
	
	void BasePanel::setSize(sf::Vector2f size) {
		Layout::resize(size, this->position);
		object->setSize(size);
	}
	
	void BasePanel::draw() {
		drawManager.draw();
	}
	
	void BasePanel::resize(sf::Vector2f size, sf::Vector2f position) {
		sf::Vector2f panelSize = (*sizing)(size);
		sf::Vector2f panelPosition = (*positioning)(position, size, panelSize);
		LayoutWithObject::resize(panelSize, panelPosition);
	}
	
	void BasePanel::update() {
		oldDisplayed = displayed;
		displayed = false;
		object->update();
	}
	
	bool BasePanel::updateInteractions(sf::Vector2f mousePosition) {
		return inPanel(mousePosition) && object->updateInteractions(mousePosition);
	}
	
	bool BasePanel::updateInteractions(sf::Vector2f mousePosition, bool active) {
		displayed = true;
		this->active = active;
		return updateInteractions(mousePosition);
	}
	
	sf::Vector2f BasePanel::getMinSize() {
		return sizing->getParentSize(object->getMinSize());
	}
	
	sf::Vector2f BasePanel::getNormalSize() {
		return sizing->getParentSize(object->getNormalSize());
	}
	
	void BasePanel::copy(BasePanel *panel) {
		Layout::copy(panel);
		panel->displayed = this->displayed;
		panel->oldDisplayed = this->oldDisplayed;
		panel->parentProcessed = this->parentProcessed;
	}
	
	bool BasePanel::fullDebug = false;
	
	void BasePanel::setFullDebug(bool fullDebug) {
		BasePanel::fullDebug = fullDebug;
	}
	
	void BasePanel::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		if(fullDebug || oldDisplayed) {
			object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		}
	}
}