
#include "PointingHidePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	PointingHidePanelInteraction::Make::Make(bool only_on_parent) :
		only_on_parent(only_on_parent) {
	}
	
	auto PointingHidePanelInteraction::Make::make(PanelActionInitInfo init_info) -> PointingHidePanelInteraction* {
		return new PointingHidePanelInteraction{std::move(*this), init_info};
	}
	
	PointingHidePanelInteraction::PointingHidePanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		panel_(&init_info.additional), panel_manager_(&init_info.panel_manager), only_on_parent_(make.only_on_parent), active_(false) {
	}
	
	auto PointingHidePanelInteraction::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto PointingHidePanelInteraction::start(sf::Vector2i) -> void {
	}
	
	auto PointingHidePanelInteraction::handle_event(Event event) -> bool {
		active_ = active_ || event.pointer().map([this](event_system::Pointer pointer) {
			if(!panel_->get_parent_processed()) {
				auto point_position{sf::Vector2f{pointer.position}};
				if(only_on_parent_ || (!panel_->in_panel(point_position) && panel_->is_free() && !panel_->in_const_panels(point_position))) {
					return true;
				}
			}
			return false;
		}).some_or(false);
		return false;
	}
	
	auto PointingHidePanelInteraction::update(sf::Vector2i) -> void {
		if(active_) {
			panel_manager_->hide_panel(panel_);
			active_ = false;
		}
	}
	
	auto PointingHidePanelInteraction::finish(sf::Vector2i) -> void {
	}
}

auto ieml::Decode<char, ie::PointingHidePanelInteraction::Make>::decode(
	ieml::Node const& node
) -> orl::Option<ie::PointingHidePanelInteraction::Make> {
	return {{node.get_as<bool>("only-on-parent").except().ok_or(false)}};
}
