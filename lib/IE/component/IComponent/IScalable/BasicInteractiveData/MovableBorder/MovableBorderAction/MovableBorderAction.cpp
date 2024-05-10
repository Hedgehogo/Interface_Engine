#include "MovableBorderAction.hpp"
#include "../MovableBorder.hpp"

namespace ie {
	MovableBorderAction::Make::Make(ISMRFloat& value) : value(value) {
	}
	
	auto MovableBorderAction::Make::make(BasicActionInitInfo<MovableBorder&> init_info) -> MovableBorderAction* {
		return new MovableBorderAction{std::move(*this), init_info};
	}
	
	MovableBorderAction::MovableBorderAction(Make&& make, BasicActionInitInfo<MovableBorder&> init_info) :
		value_(make.value),
		object_(&init_info.additional) {
	}
	
	auto MovableBorderAction::update(sf::Vector2i point_position, bool active) -> void {
		tracker_.update(active);
		if(tracker_.started()) {
			if(object_->get_is_horizontal_border()) {
				auto size{object_->get_first_object().get_size().y};
				auto position{object_->get_first_object().get_position().y};
				offset_ = static_cast<float>(point_position.y) - (position + size);
			} else {
				auto size{object_->get_first_object().get_size().x};
				auto position{object_->get_first_object().get_position().x};
				offset_ = static_cast<float>(point_position.x) - (position + size);
			}
		}
		if(tracker_.active()) {
			if(object_->get_is_horizontal_border()) {
				value_.set(((static_cast<float>(point_position.y) - offset_) - object_->get_position().y) / object_->get_size().y);
			} else {
				value_.set(((static_cast<float>(point_position.x) - offset_) - object_->get_position().x) / object_->get_size().x);
			}
		}
	}
}