#include "PointingDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	PointingDisplayPanelInteraction* PointingDisplayPanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new PointingDisplayPanelInteraction{std::move(*this), init_info};
	}
	
	PointingDisplayPanelInteraction::PointingDisplayPanelInteraction(Make&&, PanelActionInitInfo init_info) :
		BasePanelInteraction(init_info) {
	}
	
	void PointingDisplayPanelInteraction::start(sf::Vector2i) {
		panel_manager_->display_panel(panel_);
		panel_->set_parent_processed(true);
	}
	
	void PointingDisplayPanelInteraction::update(sf::Vector2i) {
	}
	
	void PointingDisplayPanelInteraction::finish(sf::Vector2i) {
		panel_->set_parent_processed(false);
	}
}

orl::Option<ie::PointingDisplayPanelInteraction::Make> ieml::Decode<char, ie::PointingDisplayPanelInteraction::Make>::decode(ieml::Node const&) {
	return {{}};
}
