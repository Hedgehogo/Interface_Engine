#include "DisplayPanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	auto DisplayPanelAction::Make::make(PanelActionInitInfo init_info) -> DisplayPanelAction* {
		return new DisplayPanelAction{std::move(*this), init_info};
	}
	
	DisplayPanelAction::DisplayPanelAction(Make&&, PanelActionInitInfo init_info) : PanelAction(init_info) {
	}
	
	auto DisplayPanelAction::update(sf::Vector2i point_position, bool active) -> void {
		if(tracker_.update(active).stopped()) {
			panel_manager_->display_panel(panel_);
		}
	}
}

auto ieml::Decode<char, ie::DisplayPanelAction::Make>::decode(ieml::Node const&) -> orl::Option<ie::DisplayPanelAction::Make> {
	return {{}};
}
