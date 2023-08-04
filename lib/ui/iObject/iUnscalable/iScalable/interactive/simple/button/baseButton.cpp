
#include "baseButton.hpp"

namespace ui {
	void BaseButton::init(InitInfo initInfo) {
		Interactive_Simple::init(initInfo);
		background->init(initInfo);
	}
	
	BaseButton::BaseButton(BoxPtr<IScalable>&& background, BoxPtr<IInteraction>&& interaction) :
		Interactive_Simple(std::move(interaction)), background(std::move(background)) {
	}
	
	void BaseButton::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
	}
	
	sf::Vector2f BaseButton::getAreaPosition() const {
		return background->getAreaPosition();
	}
	
	sf::Vector2f BaseButton::getAreaSize() const {
		return background->getAreaSize();
	}
	
	sf::Vector2f BaseButton::getMinSize() const {
		return background->getMinSize();
	}
	
	sf::Vector2f BaseButton::getNormalSize() const {
		return background->getNormalSize();
	}
	
	bool BaseButton::updateInteractions(sf::Vector2f mousePosition) {
		bool backgroundUpdate = background->updateInteractions(mousePosition);
		return Interactive_Simple::updateInteractions(mousePosition) || backgroundUpdate;
	}
	
	void BaseButton::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}