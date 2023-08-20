#include "dontMovePanelInteraction.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	DontMovePanelInteraction::DontMovePanelInteraction() : IMovePanelInteraction() {
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
	
	void DontMovePanelInteraction::init(PanelInteractionInitInfo) {
	}
	
	void DontMovePanelInteraction::setPanel(Panel&) {
	}
	
	DontMovePanelInteraction* DontMovePanelInteraction::copy() {
		return new DontMovePanelInteraction{};
	}
	
	bool DecodePointer<DontMovePanelInteraction>::decodePointer(const YAML::Node&, DontMovePanelInteraction*& dontMovePanelInteraction) {
		{
			dontMovePanelInteraction = new DontMovePanelInteraction{};
			return true;
		}
	}
}