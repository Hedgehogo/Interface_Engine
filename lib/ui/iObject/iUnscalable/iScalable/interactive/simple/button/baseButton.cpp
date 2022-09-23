#include <iostream>
#include "baseButton.hpp"

namespace ui {
	void BaseButton::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) {
		Interactive_Simple::init(renderTarget, drawManager, updateManager, panelManager);
		background->init(renderTarget, drawManager, updateManager, *interactionManager, *interactionStack, panelManager);
	}
	
	BaseButton::BaseButton(IScalable *background, IInteraction* interaction) :
		Interactive_Simple(interaction), background(background) {}
	
	BaseButton::~BaseButton() {
		delete background;
	}
	
	void BaseButton::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
	}
	
	sf::Vector2f BaseButton::getAreaPosition() {
		return background->getAreaPosition();
	}
	
	sf::Vector2f BaseButton::getAreaSize() {
		return background->getAreaSize();
	}
	
	sf::Vector2f BaseButton::getMinSize() {
		return background->getMinSize();
	}
	
	sf::Vector2f BaseButton::getNormalSize() {
		return background->getNormalSize();
	}

    bool BaseButton::updateInteractions(sf::Vector2f mousePosition) {
        bool backgroundUpdate = background->updateInteractions(mousePosition);
        return Interactive_Simple::updateInteractions(mousePosition) || backgroundUpdate;
    }

	void BaseButton::copy(BaseButton *button) {
		Interactive_Simple::copy(button);
	}

	void BaseButton::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}

}