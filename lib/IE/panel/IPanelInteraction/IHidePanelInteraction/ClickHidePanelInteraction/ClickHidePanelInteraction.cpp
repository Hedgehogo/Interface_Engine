#include "ClickHidePanelInteraction.hpp"

namespace ie {
	ClickHidePanelInteraction::Make::Make(Key key, bool only_on_parent) :
		key(key), only_on_parent(only_on_parent) {
	}
	
	ClickHidePanelInteraction* ClickHidePanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new ClickHidePanelInteraction{std::move(*this), init_info};
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		ClickPanelInteraction(make_box_ptr<HidePanelAction::Make>(make.only_on_parent), make.key, init_info) {
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(Key key, bool only_on_parent) :
		ClickPanelInteraction(make_box_ptr<HidePanelAction>(only_on_parent), key) {
	}
	
	ClickHidePanelInteraction* ClickHidePanelInteraction::copy() {
		return new ClickHidePanelInteraction{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<ClickHidePanelInteraction>::decode_pointer(const YAML::Node& node, ClickHidePanelInteraction*& click_hide_panel_interaction) {
		click_hide_panel_interaction = new ClickHidePanelInteraction{
			node["key"].as<Key>(),
			conv_def(node["only-on-parent"], false)
		};
		return true;

	}
	*/
}
