#include "DontHidePanelInteraction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	auto DontHidePanelInteraction::Make::make(PanelActionInitInfo init_info) -> DontHidePanelInteraction* {
		return new DontHidePanelInteraction{std::move(*this), init_info};
	}
	
	DontHidePanelInteraction::DontHidePanelInteraction(Make&&, PanelActionInitInfo) {
	}
	
	auto DontHidePanelInteraction::set_panel(Panel&) -> void {
	}
}

auto ieml::Decode<char, ie::DontHidePanelInteraction::Make>::decode(ieml::Node const&) -> orl::Option<ie::DontHidePanelInteraction::Make> {
	return {{}};
}
