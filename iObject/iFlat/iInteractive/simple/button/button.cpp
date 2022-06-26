#include <iostream>
#include "button.h"

namespace ui {
	void Button::init(sf::RenderTarget &renderTarget, PanelManager &panelManager) {
		initObject(background, renderTarget, *interactionStack, *interactionManager, panelManager);
	}
	
	Button::Button(IFlat *background, IInteraction* interaction) :
		Interactive_Simple(interaction), background(background) {}
	
	Button::~Button() {
		delete background;
	}
	
	void Button::draw() {
		background->draw();
	}
	
	void Button::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
	}
	
	sf::Vector2f Button::getPosition() {
		return background->getPosition();
	}
	
	sf::Vector2f Button::getSize() {
		return background->getSize();
	}
	
	sf::Vector2f Button::getMinSize() {
		return background->getMinSize();
	}
	
	sf::Vector2f Button::getNormalSize() {
		return background->getNormalSize();
	}
	
	void Button::copy(Button *button) {
		Interactive_Simple::copy(button);
	}
}