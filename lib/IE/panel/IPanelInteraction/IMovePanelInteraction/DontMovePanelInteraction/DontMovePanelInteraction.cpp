#include "DontMovePanelInteraction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	auto DontMovePanelInteraction::Make::make(PanelActionInitInfo init_info) -> DontMovePanelInteraction* {
		return new DontMovePanelInteraction{std::move(*this), init_info};
	}
	
	DontMovePanelInteraction::DontMovePanelInteraction(Make&&, PanelActionInitInfo) {
	}
	
	auto DontMovePanelInteraction::set_panel(Panel&) -> void {
	}
	
	auto DontMovePanelInteraction::move(sf::Vector2i) -> void {
	}
	
	auto DontMovePanelInteraction::start() -> void {
	}
	
	auto DontMovePanelInteraction::handle_event(Event event) -> bool {
		return false;
	}
	
	auto DontMovePanelInteraction::update() -> void {
	}
	
	auto DontMovePanelInteraction::finish() -> void {
	}
}

auto ieml::Decode<char, ie::DontMovePanelInteraction::Make>::decode(ieml::Node const&) -> orl::Option<ie::DontMovePanelInteraction::Make> {
	return {{}};
}
