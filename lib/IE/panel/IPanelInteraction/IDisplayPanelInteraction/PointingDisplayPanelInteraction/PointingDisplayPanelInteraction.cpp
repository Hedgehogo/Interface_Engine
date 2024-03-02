#include "PointingDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	auto PointingDisplayPanelInteraction::Make::make(PanelActionInitInfo init_info) -> PointingDisplayPanelInteraction* {
		return new PointingDisplayPanelInteraction{std::move(*this), init_info};
	}
	
	PointingDisplayPanelInteraction::PointingDisplayPanelInteraction(Make&&, PanelActionInitInfo init_info) :
		BasePanelInteraction(init_info) {
	}
	
	auto PointingDisplayPanelInteraction::start(sf::Vector2i) -> void {
		panel_manager_->display_panel(panel_);
		panel_->set_parent_processed(true);
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
