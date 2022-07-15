#include "basePanel.h"
#include "../panelManager/panelManager.h"

namespace ui {
	BasePanel::BasePanel(IFlat *object, Sizing2 *sizing, Positioning2 *positioning, bool displayed) :
		Layout(), object(object), sizing(sizing), positioning(positioning),
		displayed(displayed), oldDisplayed(false), parentProcessed(false), active(false) {}
	
	void BasePanel::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		panelManager.addPanel(this);
		sf::Vector2f objectNormalSize = object->getNormalSize();
		sizing->init(renderTarget, objectNormalSize);
		positioning->init(renderTarget);
	}
	
	BasePanel::~BasePanel() {
		delete object;
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
		return active &&
			   pointPosition.x >= this->position.x && pointPosition.x <= this->position.x + this->size.x &&
			   pointPosition.y >= this->position.y && pointPosition.y <= this->position.y + this->size.y;
	}
	
	void BasePanel::setPosition(sf::Vector2f position) {
		object->setPosition(position);
		Layout::resize(size, position);
	}
	
	void BasePanel::move(sf::Vector2f position) {
		Layout::resize(size, position);
		object->move(position);
	}
	
	void BasePanel::setSize(sf::Vector2f size) {
		Layout::resize(size, position);
		object->setSize(size);
	}
	
	void BasePanel::draw() {
		object->draw();
	}
	
	void BasePanel::resize(sf::Vector2f size, sf::Vector2f position) {
		sf::Vector2f panelSize = (*sizing)(size);
		sf::Vector2f panelPosition = (*positioning)(position, size, panelSize);
		Layout::resize(panelSize, panelPosition);
		object->resize(panelSize, panelPosition);
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
		return sizing->getParentMinSize(object->getMinSize());
	}
	
	sf::Vector2f BasePanel::getNormalSize() {
		return object->getNormalSize();
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