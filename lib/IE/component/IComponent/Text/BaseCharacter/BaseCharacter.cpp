#include"BaseCharacter.hpp"
#include "../BaseTextBlock/BaseTextBlock.hpp"

namespace ie {
	BaseCharacter::BaseCharacter() : selection(false), active(true), rerender(false) {
	}
	
	bool BaseCharacter::get_rerender() const {
		return rerender;
	}
	
	void BaseCharacter::set_rerender(bool rerender) {
		this->rerender = rerender;
	}
	
	void BaseCharacter::set_position(sf::Vector2f position) {
		if(this->position != position)
			rerender = true;
		this->position = position;
	}
	
	void BaseCharacter::set_kerning(float) {
	}
	
	void BaseCharacter::resize(sf::Vector2f position, float) {
		set_position(position);
	}
	
	bool BaseCharacter::in(sf::Vector2f mouse_position) {
		return position.x < mouse_position.x && position.x + get_advance() > mouse_position.x &&
			   position.y < mouse_position.y && position.y + get_height() > mouse_position.y;
	}
	
	sf::Vector2f BaseCharacter::get_position() const {
		return position;
	}
	
	void BaseCharacter::move(sf::Vector2f position) {
		if(position != sf::Vector2f{0.f, 0.f})
			rerender = true;
		this->position += position;
	}
	
	bool BaseCharacter::is_enter() {
		return is_special() == Special::Enter;
	}
	
	void BaseCharacter::set_selection(bool selection) {
		rerender = true;
		this->selection = selection;
	}
	
	void BaseCharacter::set_active(bool active) {
		rerender = true;
		this->active = active;
	}
	
	float BaseCharacter::get_min_advance() {
		return get_advance();
	}
}
