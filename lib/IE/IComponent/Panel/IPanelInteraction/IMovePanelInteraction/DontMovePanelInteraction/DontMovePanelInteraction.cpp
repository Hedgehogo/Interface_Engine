#include "DontMovePanelInteraction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	DontMovePanelInteraction* DontMovePanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new DontMovePanelInteraction{std::move(*this), initInfo};
	}
	
	DontMovePanelInteraction::DontMovePanelInteraction(Make&&, PanelActionInitInfo) {
	}
	
	bool DontMovePanelInteraction::getAtStart() {
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
	
	void DontMovePanelInteraction::setPanel(Panel&) {
	}
	
	DontMovePanelInteraction* DontMovePanelInteraction::copy() {
		return new DontMovePanelInteraction{};
	}
	
	bool DecodePointer<DontMovePanelInteraction>::decodePointer(const YAML::Node&, DontMovePanelInteraction*& dontMovePanelInteraction) {
		dontMovePanelInteraction = new DontMovePanelInteraction{};
		return true;
	}
}