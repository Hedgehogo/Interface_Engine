#include "Button.hpp"

namespace ie {
	Button::Make::Make(BoxPtr<IScalable::Make>&& background, BoxPtr<IBaseInteraction::Make>&& interaction) :
		background(std::move(background)), interaction(std::move(interaction)) {
	}
	
	auto Button::Make::make(InitInfo init_info) -> Button* {
		return new Button{std::move(*this), init_info};
	}
	
	Button::Button(Make&& make, InitInfo init_info) :
		BaseButton(std::move(make.background), init_info), interaction_(make.interaction->make({init_info, {}})) {
	}
	
	auto Button::update() -> void {
		interaction_->update();
	}
	
	auto Button::handle_event(Event event) -> bool {
		return BaseButton::handle_event(event) || interaction_->handle_event(event);
	}
}

auto ieml::Decode<char, ie::Button::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Button::Make> {
	auto map{node.get_map_view().except()};
	return ie::Button::Make{
		map.at("background").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("interaction").except().as<ie::BoxPtr<ie::IBaseInteraction::Make> >().except(),
	};
}
