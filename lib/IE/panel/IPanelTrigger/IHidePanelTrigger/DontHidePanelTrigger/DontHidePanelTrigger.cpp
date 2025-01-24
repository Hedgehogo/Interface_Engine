#include "DontHidePanelTrigger.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	auto DontHidePanelTrigger::Make::make(PanelActionInitInfo init_info) -> DontHidePanelTrigger* {
		return new DontHidePanelTrigger{std::move(*this), init_info};
	}
	
	DontHidePanelTrigger::DontHidePanelTrigger(Make&&, PanelActionInitInfo) {
	}
	
	auto DontHidePanelTrigger::set_panel(Panel&) -> void {
	}
}

auto ieml::Decode<char, ie::DontHidePanelTrigger::Make>::decode(ieml::Node const&) -> orl::Option<ie::DontHidePanelTrigger::Make> {
	return {{}};
}
