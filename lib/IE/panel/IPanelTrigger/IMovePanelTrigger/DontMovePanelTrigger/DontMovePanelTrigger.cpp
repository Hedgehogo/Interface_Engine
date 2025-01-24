#include "DontMovePanelTrigger.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	auto DontMovePanelTrigger::Make::make(PanelActionInitInfo init_info) -> DontMovePanelTrigger* {
		return new DontMovePanelTrigger{std::move(*this), init_info};
	}
	
	DontMovePanelTrigger::DontMovePanelTrigger(Make&&, PanelActionInitInfo) {
	}
	
	auto DontMovePanelTrigger::set_panel(Panel&) -> void {
	}
	
	auto DontMovePanelTrigger::move(sf::Vector2i) -> void {
	}
	
	auto DontMovePanelTrigger::start() -> void {
	}
	
	auto DontMovePanelTrigger::handle_event(Event event) -> bool {
		return false;
	}
	
	auto DontMovePanelTrigger::update() -> void {
	}
	
	auto DontMovePanelTrigger::finish() -> void {
	}
}

auto ieml::Decode<char, ie::DontMovePanelTrigger::Make>::decode(ieml::Node const&) -> orl::Option<ie::DontMovePanelTrigger::Make> {
	return {{}};
}
