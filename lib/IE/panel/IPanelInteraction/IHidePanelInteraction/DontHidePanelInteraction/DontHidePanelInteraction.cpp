#include "DontHidePanelInteraction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	DontHidePanelInteraction* DontHidePanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new DontHidePanelInteraction{std::move(*this), init_info};
	}
	
	DontHidePanelInteraction::DontHidePanelInteraction(Make&&, PanelActionInitInfo) {
	}
	
	void DontHidePanelInteraction::set_panel(Panel&) {
	}
}

orl::Option<ie::DontHidePanelInteraction::Make> ieml::Decode<char, ie::DontHidePanelInteraction::Make>::decode(ieml::Node const&) {
	return {{}};
}
