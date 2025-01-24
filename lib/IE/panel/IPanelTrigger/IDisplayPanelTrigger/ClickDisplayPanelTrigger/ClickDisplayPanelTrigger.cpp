#include "ClickDisplayPanelTrigger.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	ClickDisplayPanelTrigger::Make::Make(Key key) : key(key) {
	}
	
	auto ClickDisplayPanelTrigger::Make::make(PanelActionInitInfo init_info) -> ClickDisplayPanelTrigger* {
		return new ClickDisplayPanelTrigger{std::move(*this), init_info};
	}
	
	ClickDisplayPanelTrigger::ClickDisplayPanelTrigger(Make&& make, PanelActionInitInfo init_info) :
		ClickPanelTrigger(make_box_ptr<DisplayPanelAction::Make>(), make.key, init_info) {
	}
	
	auto ClickDisplayPanelTrigger::start() -> void {
		dynamic_cast<PanelAction&>(*action_).get_panel()->set_parent_processed(true);
	}
	
	auto ClickDisplayPanelTrigger::finish() -> void {
		BasicTouchTrigger<Panel&>::finish();
		dynamic_cast<PanelAction&>(*action_).get_panel()->set_parent_processed(false);
	}
}

auto ieml::Decode<char, ie::ClickDisplayPanelTrigger::Make>::decode(
	ieml::Node const& node
) -> orl::Option<ie::ClickDisplayPanelTrigger::Make> {
	return {{node.at("key").except().as<ie::Key>().except()}};
}
