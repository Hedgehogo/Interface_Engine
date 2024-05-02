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
		object_(&init_info.additional){
	}
	
	auto MovableBorderAction::start_pressed() -> void {
		if(object_->get_is_horizontal_border()) {
			offset_ = static_cast<float>(point_position_.y) - (object_->get_first_object().get_size().y + object_->get_first_object().get_position().y);
		} else {
			offset_ = static_cast<float>(point_position_.x) - (object_->get_first_object().get_size().x + object_->get_first_object().get_position().x);
		}
	}
	
	auto MovableBorderAction::stop_pressed() -> void {
	}
	
	auto MovableBorderAction::while_pressed() -> void {
		if (object_->get_is_horizontal_border()){
			value_.set(((static_cast<float>(point_position_.y) - offset_) - object_->get_position().y) / object_->get_size().y);
		} else {
			value_.set(((static_cast<float>(point_position_.x) - offset_) - object_->get_position().x) / object_->get_size().x);
		}
	}
	
	auto MovableBorderAction::while_not_pressed() -> void {
	}
}