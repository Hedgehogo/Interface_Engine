
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
		BasePanelInteraction(init_info), only_on_parent_(make.only_on_parent) {
	}
	
	auto PointingHidePanelInteraction::start(sf::Vector2i) -> void {
	}
	
	auto PointingHidePanelInteraction::handle_event(Event event) -> bool {
		return false;
	}
	
	auto PointingHidePanelInteraction::update(sf::Vector2i mouse_position) -> void {
		auto point_position{sf::Vector2f{mouse_position}};
		if(!panel_->get_parent_processed()) {
			if(only_on_parent_ || (!panel_->in_panel(point_position) && panel_->is_free() && !panel_->in_const_panels(point_position))) {
				panel_manager_->hide_panel(panel_);
			}
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
