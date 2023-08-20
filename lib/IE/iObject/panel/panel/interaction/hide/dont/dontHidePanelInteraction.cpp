#include "dontHidePanelInteraction.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	void DontHidePanelInteraction::init(PanelInteractionInitInfo) {
	}
	
	void DontHidePanelInteraction::setPanel(Panel&) {
	}
	
	DontHidePanelInteraction* DontHidePanelInteraction::copy() {
		return new DontHidePanelInteraction{};
	}
	
	bool DecodePointer<DontHidePanelInteraction>::decodePointer(const YAML::Node&, DontHidePanelInteraction*& dontHidePanelInteraction) {
		{
			dontHidePanelInteraction = new DontHidePanelInteraction{};
			return true;
		}
	}
}