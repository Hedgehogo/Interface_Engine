#include "dontMovePanelInteraction.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	DontMovePanelInteraction::DontMovePanelInteraction() : MovePanelInteraction() {
	}
	
	void DontMovePanelInteraction::move(sf::Vector2i mousePosition) {
	}
	
	void DontMovePanelInteraction::start(sf::Vector2i mousePosition) {
	}
	
	void DontMovePanelInteraction::update(sf::Vector2i mousePosition) {
	}
	
	void DontMovePanelInteraction::init(Panel& panel, IPanelManager& panelManager) {
	}
	
	void DontMovePanelInteraction::setPanel(Panel& panel) {
	}
	
	DontMovePanelInteraction* DontMovePanelInteraction::copy() {
		return new DontMovePanelInteraction{};
	}
	
	
	bool DecodePointer<DontMovePanelInteraction>::decodePointer(const YAML::Node& node, DontMovePanelInteraction*& dontMovePanelInteraction) {
		{
			dontMovePanelInteraction = new DontMovePanelInteraction{};
			return true;
		}
	}
}