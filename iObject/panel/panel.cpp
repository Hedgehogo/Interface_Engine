#include "panel.h"
#include "interaction/hidePanelInteraction.h"
#include "interaction/pointingHidePanelInteraction/pointingHidePanelInteraction.h"

ui::Panel::Panel(IFlat *object, Size verticalSize, Size horizontalSize, sf::Vector2f size, bool displayed) :
	object(object), verticalSize(verticalSize), horizontalSize(horizontalSize), size(size), interaction(), position(0, 0), displayed(false), active(false), parentProcessed(false) {
	sf::Vector2f objectNormalSize = object->getNormalSize();
	if(horizontalSize == Size::regardingChild)
		this->size.x = objectNormalSize.x;
	if(verticalSize == Size::regardingChild)
		this->size.y = objectNormalSize.y;
}

ui::Panel::Panel(ui::IFlat *object, sf::Vector2f size, bool displayed) :
	object(object), verticalSize(Size::constant), horizontalSize(Size::constant), size(size), interaction(new PointingHidePanelInteraction{}), position(0, 0), displayed(false), active(false) {
	
}
void ui::Panel::init(sf::RenderWindow &window, InteractionStack &interactionStack, ui::InteractionManager &interactionManager, ui::Panel *parent, ui::PanelStack &panelStack) {
	this->interactionManager = &interactionManager;
	initObject(object, window, interactionStack, interactionManager, parent, panelStack);
	interaction->init(*this, panelStack);
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

void ui::Panel::hide() {
	interactionManager->deleteInteraction(*interaction);
	displayed = false;
}

bool ui::Panel::isActive() {
	return active;
}

void ui::Panel::draw() {
	object->draw();
}

void ui::Panel::resize(sf::Vector2f size, sf::Vector2f position) {
	if(horizontalSize == Size::regardingParent)
		this->size.x = size.x;
	if(verticalSize == Size::regardingParent)
		this->size.y = size.y;
	object->resize(this->size, position);
}

void ui::Panel::update() {
	if(!displayed) {
		interactionManager->addInteraction(*interaction);
		displayed = true;
	}
	object->update();
}

bool ui::Panel::inPanel(sf::Vector2f position) {
	return position.x >= this->position.x && position.x <= this->position.x + this->size.x &&
		   position.y >= this->position.y && position.y <= this->position.y + this->size.y;
}

bool ui::Panel::updateInteractions(sf::Vector2f mousePosition) {
	return object->updateInteractions(mousePosition);
}

bool ui::Panel::updateInteractions(bool active, sf::Vector2f mousePosition) {
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
