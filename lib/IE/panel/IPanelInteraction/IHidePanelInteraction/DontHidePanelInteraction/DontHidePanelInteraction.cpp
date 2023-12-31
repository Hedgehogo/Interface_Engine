#include "DontHidePanelInteraction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	DontHidePanelInteraction* DontHidePanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new DontHidePanelInteraction{std::move(*this), init_info};
	}
	
	DontHidePanelInteraction::DontHidePanelInteraction(Make&&, PanelActionInitInfo) {
	}
	
	void DontHidePanelInteraction::init(PanelActionInitInfo) {
	}
	
	void DontHidePanelInteraction::set_panel(Panel&) {
	}
	
	DontHidePanelInteraction* DontHidePanelInteraction::copy() {
		return new DontHidePanelInteraction{};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<DontHidePanelInteraction>::decode_pointer(const YAML::Node&, DontHidePanelInteraction*& dont_hide_panel_interaction) {
		dont_hide_panel_interaction = new DontHidePanelInteraction{};
		return true;
	}
	*/
}