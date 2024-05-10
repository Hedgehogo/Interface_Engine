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
	
	auto MovableBorderAction::update(orl::Option<Touch> touch) -> void {
		auto const pressing{Touch::pressing(touch)};
		for(auto const point_position: pressing) {
			if(!active) {
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
			if(object_->get_is_horizontal_border()) {
				value_.set(((static_cast<float>(point_position.y) - offset_) - object_->get_position().y) / object_->get_size().y);
			} else {
				value_.set(((static_cast<float>(point_position.x) - offset_) - object_->get_position().x) / object_->get_size().x);
			}
		}
		active = pressing.is_some();
	}
}