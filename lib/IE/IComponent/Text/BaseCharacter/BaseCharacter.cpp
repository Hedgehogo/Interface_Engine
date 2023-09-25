#include"BaseCharacter.hpp"
#include "../BaseTextBlock/BaseTextBlock.hpp"

namespace ie {
	BaseCharacter::BaseCharacter() : selection(false), rerender(false) {
	}
	
	bool BaseCharacter::getRerender() const {
		return rerender;
	}
	
	void BaseCharacter::setRerender(bool rerender) {
		this->rerender = rerender;
	}
	
	void BaseCharacter::setPosition(sf::Vector2f position) {
		if(this->position != position)
			rerender = true;
		this->position = position;
	}
	
	void BaseCharacter::resize(sf::Vector2f position, float) {
		setPosition(position);
	}
	
	bool BaseCharacter::in(sf::Vector2f mousePosition) {
		return position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
			   position.y < mousePosition.y && position.y + getHeight() > mousePosition.y;
	}
	
	sf::Vector2f BaseCharacter::getPosition() const {
		return position;
	}
	
	void BaseCharacter::move(sf::Vector2f position) {
		if(position != sf::Vector2f{0.f, 0.f})
			rerender = true;
		this->position += position;
	}
	
	bool BaseCharacter::isEnter() {
		return isSpecial() == Special::Enter;
	}
	
	void BaseCharacter::setSelection(bool selection) {
		rerender = true;
		this->selection = selection;
	}
	
	void BaseCharacter::setActive(bool active) {
		rerender = true;
		this->active = active;
	}
	
	float BaseCharacter::getMinAdvance() {
		return getAdvance();
	}
}
