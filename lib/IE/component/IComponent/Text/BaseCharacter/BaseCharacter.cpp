#include"BaseCharacter.hpp"
#include "../BaseTextBlock/BaseTextBlock.hpp"

namespace ie {
	BaseCharacter::BaseCharacter() : selection_(false), active_(true), rerender_(false) {
	}
	
	auto BaseCharacter::get_rerender() const -> bool {
		return rerender_;
	}
	
	auto BaseCharacter::set_rerender(bool rerender) -> void {
		this->rerender_ = rerender;
	}
	
	auto BaseCharacter::set_position(sf::Vector2f position) -> void {
		if(this->position_ != position) {
			rerender_ = true;
		}
		this->position_ = position;
	}
	
	auto BaseCharacter::set_kerning(float) -> void {
	}
	
	auto BaseCharacter::resize(sf::Vector2f position, float) -> void {
		set_position(position);
	}
	
	auto BaseCharacter::in(sf::Vector2f point_position) -> bool {
		return
			position_.x < point_position.x && position_.x + get_advance() > point_position.x &&
			position_.y < point_position.y && position_.y + get_height() > point_position.y;
	}
	
	auto BaseCharacter::get_position() const -> sf::Vector2f {
		return position_;
	}
	
	auto BaseCharacter::move(sf::Vector2f offset) -> void {
		if(offset != sf::Vector2f{}) {
			rerender_ = true;
		}
		this->position_ += offset;
	}
	
	auto BaseCharacter::is_enter() -> bool {
		return is_special() == Special::Enter;
	}
	
	auto BaseCharacter::set_selection(bool selection) -> void {
		rerender_ = true;
		this->selection_ = selection;
	}
	
	auto BaseCharacter::set_active(bool active) -> void {
		rerender_ = true;
		this->active_ = active;
	}
	
	auto BaseCharacter::get_min_advance() -> float {
		return get_advance();
	}
}
