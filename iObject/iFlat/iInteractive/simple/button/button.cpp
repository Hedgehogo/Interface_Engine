#include <iostream>
#include "button.h"

namespace ui {
	void Button::init(sf::RenderWindow &window, PanelManager &panelManager) {
		initObject(background, window, *interactionStack, *interactionManager, panelManager);
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