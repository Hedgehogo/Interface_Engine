#include "panel.h"
#include "panelManager/panelManager.h"
#include "interaction/hide/hidePanelInteraction.h"

ui::Panel::Panel(IFlat *object, HidePanelInteraction *interaction, Corner parentCorner, Corner panelCorner, sf::Vector2f offset, Size verticalSize, Size horizontalSize, sf::Vector2f size, bool displayed) :
	Layout(size), object(object), verticalSize(verticalSize), horizontalSize(horizontalSize), parentCorner(parentCorner), panelCorner(panelCorner), offset(offset),
	interaction(interaction), displayed(displayed), oldDisplayed(false), active(false), parentProcessed(false), interactionManager(nullptr) {
	sf::Vector2f objectNormalSize = object->getNormalSize();
	if(horizontalSize == Size::regardingChild)
		this->size.x = objectNormalSize.x;
	if(verticalSize == Size::regardingChild)
		this->size.y = objectNormalSize.y;
}

ui::Panel::Panel(IFlat *object, HidePanelInteraction *interaction, sf::Vector2f size, Corner parentCorner, Corner panelCorner, sf::Vector2f offset, bool displayed) :
	Layout(size), object(object), verticalSize(Size::constant), horizontalSize(Size::constant), parentCorner(parentCorner), panelCorner(panelCorner), offset(offset),
	interaction(interaction), displayed(displayed), oldDisplayed(false), active(false), parentProcessed(false), interactionManager(nullptr) {}

void ui::Panel::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	initObject(object, window, interactionStack, interactionManager, panelManager);
	this->interactionManager = &interactionManager;
	interaction->init(*this, panelManager);
	panelManager.addPanel(this);
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

sf::Vector2f ui::Panel::cornerToPositionOffset(ui::Corner corner, sf::Vector2f size) {
	sf::Vector2f offset{0, 0};
	if(corner == Corner::UpRight || corner == Corner::DownRight) {
		offset.x += size.x;
	}
	if(corner == Corner::DownLeft || corner == Corner::DownRight) {
		offset.y += size.y;
	}
	return offset;
}

void ui::Panel::draw() {
	object->draw();
}

void ui::Panel::resize(sf::Vector2f size, sf::Vector2f position) {
	if(horizontalSize == Size::regardingParent)
		this->size.x = size.x;
	if(verticalSize == Size::regardingParent)
		this->size.y = size.y;
	this->position = position + offset + cornerToPositionOffset(parentCorner, size) - cornerToPositionOffset(panelCorner, this->size);
	object->resize(this->size, this->position);
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
	Panel* panel {new Panel(object->copy(), interaction->copy(), parentCorner, panelCorner, offset, verticalSize, horizontalSize, size, displayed)};
	panel->interaction->setPanel(*panel);
	Panel::copy(panel);
	return panel;
}
