#include "Button.hpp"

namespace ie {
	Button::Make::Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseTrigger::Make>&& trigger) :
		background(std::move(background)), trigger(std::move(trigger)) {
	}
	
	auto Button::Make::make(InitInfo init_info) -> Button* {
		return new Button{std::move(*this), init_info};
	}
	
	Button::Button(Make&& make, InitInfo init_info) :
		BaseButton(std::move(make.background), init_info), trigger_(make.trigger->make({init_info, {}})) {
	}
	
	auto Button::update() -> void {
		trigger_->update();
	}
	
	auto Button::handle_event(Event event) -> bool {
		return BaseButton::handle_event(event) || trigger_->handle_event(event);
	}
}

auto ieml::Decode<char, ie::Button::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Button::Make> {
	auto map{node.get_map_view().except()};
	return ie::Button::Make{
		map.at("background").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("trigger").except().as<ie::BoxPtr<ie::IBaseTrigger::Make> >().except(),
	};
}
