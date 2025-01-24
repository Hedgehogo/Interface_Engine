#include "DisplayPanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	auto DisplayPanelAction::Make::make(PanelActionInitInfo init_info) -> DisplayPanelAction* {
		return new DisplayPanelAction{std::move(*this), init_info};
	}
	
	DisplayPanelAction::DisplayPanelAction(Make&&, PanelActionInitInfo init_info) : PanelAction(init_info) {
	}
	
	auto DisplayPanelAction::update(orl::Option<Touch> touch) -> void {
		if(tracker_.update(Touch::pressing(touch).is_some()).stopped()) {
			panel_manager_->display_panel(panel_);
		}
	}
}

auto ieml::Decode<char, ie::DisplayPanelAction::Make>::decode(ieml::Node const&) -> orl::Option<ie::DisplayPanelAction::Make> {
	return {{}};
}
