#include <iostream>
#include "button.h"

namespace ui {
	void Button::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, PanelManager &panelManager) {
		background->init(renderTarget, drawManager, *interactionManager, *interactionStack, panelManager);
	}
	
	Button::Button(IScalable *background, IInteraction* interaction) :
		Interactive_Simple(interaction), background(background) {}
	
	Button::~Button() {
		delete background;
	}
	
	void Button::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
	}
	
	sf::Vector2f Button::getAreaPosition() {
		return background->getAreaPosition();
	}
	
	sf::Vector2f Button::getAreaSize() {
		return background->getAreaSize();
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
	
	void Button::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}