#include "FnPositioning2.hpp"

namespace ie {
	FnPositioning2::Make::Make(FindPositionFn find_position_fn) :
		find_position_fn(std::move(find_position_fn)) {
	}
	
	FnPositioning2* FnPositioning2::Make::make(Positioning2InitInfo init_info) {
		return new FnPositioning2{std::move(*this), init_info};
	}
	
	FnPositioning2::FnPositioning2(Make&& make, Positioning2InitInfo init_info) :
		find_position_fn_(std::move(make.find_position_fn)), render_target_(&init_info.render_target) {
	}
	
	FnPositioning2::FnPositioning2(FindPositionFn find_position_fn) :
		find_position_fn_(std::move(find_position_fn)), render_target_(nullptr) {
	}
	
	void FnPositioning2::init(sf::RenderTarget& render_target) {
		this->render_target_ = &render_target;
	}
	
	sf::Vector2f FnPositioning2::find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) {
		sf::Vector2f target_size{render_target_->getSize()};
		return find_position_fn_(parent_position, parent_size, object_size, target_size);
	}
	
	FnPositioning2* FnPositioning2::copy() {
		return new FnPositioning2{*this};
	}
}