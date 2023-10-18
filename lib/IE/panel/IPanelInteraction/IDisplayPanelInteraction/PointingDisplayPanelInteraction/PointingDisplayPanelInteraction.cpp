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
		panel_manager->display_panel(panel);
		panel->set_parent_processed(true);
	}
	
	void PointingDisplayPanelInteraction::update(sf::Vector2i) {
	}
	
	void PointingDisplayPanelInteraction::finish(sf::Vector2i) {
		panel->set_parent_processed(false);
	}
	
	PointingDisplayPanelInteraction* PointingDisplayPanelInteraction::copy() {
		return new PointingDisplayPanelInteraction{*this};
	}
	
	bool DecodePointer<PointingDisplayPanelInteraction>::decode_pointer(const YAML::Node&, PointingDisplayPanelInteraction*& pointing_display_panel_interaction) {
		pointing_display_panel_interaction = new PointingDisplayPanelInteraction{};
		return true;
	}
}

