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
}

orl::Option<ie::DontMovePanelInteraction::Make> ieml::Decode<char, ie::DontMovePanelInteraction::Make>::decode(ieml::Node const&) {
	return {{}};
}
