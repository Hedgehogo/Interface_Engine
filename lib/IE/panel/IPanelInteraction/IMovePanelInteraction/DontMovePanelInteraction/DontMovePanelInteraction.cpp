#include "DontMovePanelInteraction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	DontMovePanelInteraction* DontMovePanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new DontMovePanelInteraction{std::move(*this), init_info};
	}
	
	DontMovePanelInteraction::DontMovePanelInteraction(Make&&, PanelActionInitInfo) {
	}
	
	bool DontMovePanelInteraction::get_at_start() {
		return false;
	}
	
	void DontMovePanelInteraction::move(sf::Vector2i) {
	}
	
	void DontMovePanelInteraction::start(sf::Vector2i) {
	}
	
	void DontMovePanelInteraction::update(sf::Vector2i) {
	}
	
	void DontMovePanelInteraction::init(PanelActionInitInfo) {
	}
	
	void DontMovePanelInteraction::set_panel(Panel&) {
	}
	
	DontMovePanelInteraction* DontMovePanelInteraction::copy() {
		return new DontMovePanelInteraction{};
	}
	
	bool DecodePointer<DontMovePanelInteraction>::decode_pointer(const YAML::Node&, DontMovePanelInteraction*& dont_move_panel_interaction) {
		dont_move_panel_interaction = new DontMovePanelInteraction{};
		return true;
	}
}