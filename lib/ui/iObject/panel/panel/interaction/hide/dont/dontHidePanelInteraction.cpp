#include "dontHidePanelInteraction.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	void DontHidePanelInteraction::init(PanelInteractionInitInfo panelInteractionInitInfo) {
	}
	
	void DontHidePanelInteraction::setPanel(Panel& panel) {
	}
	
	DontHidePanelInteraction* DontHidePanelInteraction::copy() {
		return new DontHidePanelInteraction{};
	}
	
	
	bool DecodePointer<DontHidePanelInteraction>::decodePointer(const YAML::Node& node, DontHidePanelInteraction*& dontHidePanelInteraction) {
		{
			dontHidePanelInteraction = new DontHidePanelInteraction{};
			return true;
		}
	}
}