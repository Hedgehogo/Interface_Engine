#include "baseCharacter.hpp"
#include "../textBlock/baseTextBlock.hpp"

namespace ui {
	BaseCharacter::BaseCharacter() : selection(false) {}
	
	void BaseCharacter::init(sf::RenderTarget &renderTarget) {}
	
	void BaseCharacter::setPosition(sf::Vector2f position) {
		this->position = position;
	}
	
	bool BaseCharacter::in(sf::Vector2f mousePosition) {
		return position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
			   position.y < mousePosition.y && position.y + getHeight() > mousePosition.y;
	}
	
	const sf::Vector2f &BaseCharacter::getPosition() const {
		return position;
	}
	
	void BaseCharacter::move(sf::Vector2f position) {
		this->position += position;
	}
	
	bool BaseCharacter::isEnter() {
		return isSpecial() == Special::enter;
	}
	
	void BaseCharacter::setSelection(bool selection) {
		this->selection = selection;
	}
	
	void BaseCharacter::setActive(bool active) {
		this->active = active;
	}
}
