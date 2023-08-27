#include "DontHidePanelInteraction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	DontHidePanelInteraction* DontHidePanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new DontHidePanelInteraction{std::move(*this), initInfo};
	}
	
	DontHidePanelInteraction::DontHidePanelInteraction(Make&&, PanelActionInitInfo) {
	}
	
	void DontHidePanelInteraction::init(PanelActionInitInfo) {
	}
	
	void DontHidePanelInteraction::setPanel(Panel&) {
	}
	
	DontHidePanelInteraction* DontHidePanelInteraction::copy() {
		return new DontHidePanelInteraction{};
	}
	
	bool DecodePointer<DontHidePanelInteraction>::decodePointer(const YAML::Node&, DontHidePanelInteraction*& dontHidePanelInteraction) {
		dontHidePanelInteraction = new DontHidePanelInteraction{};
		return true;
	}
}