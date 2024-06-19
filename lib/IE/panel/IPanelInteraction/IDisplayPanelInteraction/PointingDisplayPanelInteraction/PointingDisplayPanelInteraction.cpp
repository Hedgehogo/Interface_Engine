#include "PointingDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	auto PointingDisplayPanelInteraction::Make::make(PanelActionInitInfo init_info) -> PointingDisplayPanelInteraction* {
		return new PointingDisplayPanelInteraction{std::move(*this), init_info};
	}
	
	PointingDisplayPanelInteraction::PointingDisplayPanelInteraction(Make&&, PanelActionInitInfo init_info) :
		panel_(&init_info.additional),
		panel_manager_(&init_info.panel_manager) {
	}
	
	auto PointingDisplayPanelInteraction::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto PointingDisplayPanelInteraction::start(sf::Vector2i) -> void {
		panel_manager_->display_panel(panel_);
		panel_->set_parent_processed(true);
	}
	
	auto PointingDisplayPanelInteraction::handle_event(Event event) -> bool {
		return false;
	}
	
	auto PointingDisplayPanelInteraction::update(sf::Vector2i) -> void {
	}
	
	auto PointingDisplayPanelInteraction::finish(sf::Vector2i) -> void {
		panel_->set_parent_processed(false);
	}
}

auto ieml::Decode<char, ie::PointingDisplayPanelInteraction::Make>::decode(
	ieml::Node const&
) -> orl::Option<ie::PointingDisplayPanelInteraction::Make> {
	return {{}};
}
