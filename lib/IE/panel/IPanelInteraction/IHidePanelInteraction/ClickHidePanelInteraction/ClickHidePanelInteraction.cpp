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
}

orl::Option<ie::ClickHidePanelInteraction::Make> ieml::Decode<char, ie::ClickHidePanelInteraction::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::ClickHidePanelInteraction::Make{
		map.at("key").except().as<ie::Key>().except(),
		map.get_as<bool>("only-on-parent").except().ok_or(false),
	};
}
