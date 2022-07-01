#include "panel.h"
#include "panelManager/panelManager.h"
#include "interaction/hide/hidePanelInteraction.h"

ui::Panel::Panel(IFlat *object, HidePanelInteraction *interaction, Sizing2* sizing, Positioning2* positioning, bool displayed) :
	Layout(), object(object), sizing(sizing), positioning(positioning),
	interaction(interaction), displayed(displayed), oldDisplayed(false), active(false), parentProcessed(false), interactionManager(nullptr) {
}

void ui::Panel::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	initObject(object, renderTarget, interactionStack, interactionManager, panelManager);
	this->interactionManager = &interactionManager;
	interaction->init(*this, panelManager);
	panelManager.addPanel(this);
	
	sf::Vector2f objectNormalSize = object->getNormalSize();
	sizing->init(renderTarget, objectNormalSize);
	positioning->init(renderTarget);
}

ui::Panel::~Panel() {
	delete object;
	delete interaction;
}

void ui::Panel::setParentProcessed(bool parentProcessed) {
	this->parentProcessed = parentProcessed;
}

bool ui::Panel::getParentProcessed() {
	return parentProcessed;
}

bool ui::Panel::isActive() {
	return active;
}

void ui::Panel::draw() {
	object->draw();
}

void ui::Panel::resize(sf::Vector2f size, sf::Vector2f position) {
	sf::Vector2f panelSize = (*sizing)(size);
	sf::Vector2f panelPosition = (*positioning)(position, size, panelSize);
	Layout::resize(panelSize, panelPosition);
	object->resize(panelSize, panelPosition);
}

void ui::Panel::update() {
	if(oldDisplayed != displayed) {
		if(displayed) {
			interactionManager->addInteraction(*interaction);
		} else {
			interactionManager->deleteInteraction(*interaction);
		}
	}
	oldDisplayed = displayed;
	displayed = false;
	object->update();
}

bool ui::Panel::inPanel(sf::Vector2f pointPosition) {
	return pointPosition.x >= this->position.x && pointPosition.x <= this->position.x + this->size.x &&
		   pointPosition.y >= this->position.y && pointPosition.y <= this->position.y + this->size.y;
}

bool ui::Panel::updateInteractions(sf::Vector2f mousePosition) {
	return object->updateInteractions(mousePosition);
}

bool ui::Panel::updateInteractions(bool active, sf::Vector2f mousePosition) {
	displayed = true;
	this->active = active;
	if(this->active && inPanel(mousePosition)) {
		return updateInteractions(mousePosition);
	}
	return false;
}

sf::Vector2f ui::Panel::getNormalSize() {
	return object->getNormalSize();
}

sf::Vector2f ui::Panel::getMinSize() {
	return object->getMinSize();
}

void ui::Panel::copy(ui::Panel *panel) {
	panel->position = this->position;
	panel->interactionManager = this->interactionManager;
	panel->parentProcessed = this->parentProcessed;
	panel->active = this->active;
}

ui::Panel *ui::Panel::copy() {
	Panel* panel {new Panel(object->copy(), interaction->copy(), sizing->copy(), positioning->copy(), displayed)};
	panel->interaction->setPanel(*panel);
	Panel::copy(panel);
	return panel;
}
