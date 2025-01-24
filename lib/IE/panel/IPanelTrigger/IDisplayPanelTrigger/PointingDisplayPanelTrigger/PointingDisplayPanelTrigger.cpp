#include "PointingDisplayPanelTrigger.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	auto PointingDisplayPanelTrigger::Make::make(PanelActionInitInfo init_info) -> PointingDisplayPanelTrigger* {
		return new PointingDisplayPanelTrigger{std::move(*this), init_info};
	}
	
	PointingDisplayPanelTrigger::PointingDisplayPanelTrigger(Make&&, PanelActionInitInfo init_info) :
		panel_(&init_info.additional),
		panel_manager_(&init_info.panel_manager) {
	}
	
	auto PointingDisplayPanelTrigger::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto PointingDisplayPanelTrigger::start() -> void {
		panel_manager_->display_panel(panel_);
		panel_->set_parent_processed(true);
	}
	
	auto PointingDisplayPanelTrigger::handle_event(Event event) -> bool {
		return false;
	}
	
	auto PointingDisplayPanelTrigger::update() -> void {
	}
	
	auto PointingDisplayPanelTrigger::finish() -> void {
		panel_->set_parent_processed(false);
	}
}

auto ieml::Decode<char, ie::PointingDisplayPanelTrigger::Make>::decode(
	ieml::Node const&
) -> orl::Option<ie::PointingDisplayPanelTrigger::Make> {
	return {{}};
}
