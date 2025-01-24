#include "ClickHidePanelTrigger.hpp"

namespace ie {
	ClickHidePanelTrigger::Make::Make(Key key, bool only_on_parent) :
		key(key), only_on_parent(only_on_parent) {
	}
	
	auto ClickHidePanelTrigger::Make::make(PanelActionInitInfo init_info) -> ClickHidePanelTrigger* {
		return new ClickHidePanelTrigger{std::move(*this), init_info};
	}
	
	ClickHidePanelTrigger::ClickHidePanelTrigger(Make&& make, PanelActionInitInfo init_info) :
		ClickPanelTrigger(make_box_ptr<HidePanelAction::Make>(make.only_on_parent), make.key, init_info) {
	}
}

auto ieml::Decode<char, ie::ClickHidePanelTrigger::Make>::decode(ieml::Node const& node) -> orl::Option<ie::ClickHidePanelTrigger::Make> {
	auto map{node.get_map_view().except()};
	return ie::ClickHidePanelTrigger::Make{
		map.at("key").except().as<ie::Key>().except(),
		map.get_as<bool>("only-on-parent").except().ok_or(false),
	};
}
