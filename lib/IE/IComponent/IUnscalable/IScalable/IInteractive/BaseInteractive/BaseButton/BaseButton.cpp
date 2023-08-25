
#include "BaseButton.hpp"

namespace ui {
	BaseButton::BaseButton(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction>&& interaction, InitInfo initInfo) :
		BaseInteractive(std::move(interaction), initInfo), background(background->make(initInfo)) {
	}
	
	BaseButton::BaseButton(BoxPtr<IScalable>&& background, BoxPtr<IBaseInteraction>&& interaction) :
		BaseInteractive(std::move(interaction)), background(std::move(background)) {
	}
	
	void BaseButton::init(InitInfo initInfo) {
		BaseInteractive::init(initInfo);
		background->init(initInfo);
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
	
	const IScalable& BaseButton::getBackground() const {
		return *background;
	}
	
	bool BaseButton::updateInteractions(sf::Vector2f mousePosition) {
		bool backgroundUpdate = background->updateInteractions(mousePosition);
		return BaseInteractive::updateInteractions(mousePosition) || backgroundUpdate;
	}
	
	void BaseButton::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}