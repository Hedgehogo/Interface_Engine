#include "FnPositioning2.hpp"

namespace ie {
	FnPositioning2::Make::Make(FindPositionFn find_position_fn) :
		find_position_fn(std::move(find_position_fn)) {
	}
	
	auto FnPositioning2::Make::make(Positioning2InitInfo init_info) -> FnPositioning2* {
		return new FnPositioning2{std::move(*this), init_info};
	}
	
	FnPositioning2::FnPositioning2(Make&& make, Positioning2InitInfo init_info) :
		find_position_fn_(std::move(make.find_position_fn)), render_target_(&init_info.render_target) {
	}
	
	auto FnPositioning2::find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) -> sf::Vector2f {
		sf::Vector2f target_size{render_target_->getSize()};
		return find_position_fn_(parent_position, parent_size, object_size, target_size);
	}
}