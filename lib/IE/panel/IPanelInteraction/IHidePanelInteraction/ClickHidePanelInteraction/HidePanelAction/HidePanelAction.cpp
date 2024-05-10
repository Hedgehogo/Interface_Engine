#include "HidePanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	HidePanelAction::Make::Make(bool only_on_parent) : only_on_parent(only_on_parent) {
	}
	
	HidePanelAction* HidePanelAction::Make::make(PanelActionInitInfo init_info) {
		return new HidePanelAction{std::move(*this), init_info};
	}
	
	HidePanelAction::HidePanelAction(Make&& make, PanelActionInitInfo init_info) :
		PanelAction(init_info), pressing(), only_on_parent_(make.only_on_parent) {
	}
	
	auto HidePanelAction::update(orl::Option<Touch> touch) -> void {
		pressing = touch.and_then([](Touch value) -> orl::Option<orl::Option<sf::Vector2f> > {
			return value.active && orl::Option{sf::Vector2f{value.position}};
		}).some_or_else([this] {
			for(auto point_position: pressing) {
				if(
					only_on_parent_ ?
					panel_->get_parent_processed() :
					!panel_->in_panel(point_position) && !panel_->in_const_panels(point_position) && panel_->is_free()
					) {
					panel_manager_->hide_panel(panel_);
				}
			}
			return orl::Option<sf::Vector2f>{};
		});
	}
}

auto ieml::Decode<char, ie::HidePanelAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::HidePanelAction::Make> {
	return {{node.get_as<bool>("only-on-parent").except().ok_or(false)}};
}
