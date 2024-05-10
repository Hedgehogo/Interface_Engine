#include "HidePanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	HidePanelAction::Make::Make(bool only_on_parent) : only_on_parent(only_on_parent) {
	}
	
	HidePanelAction* HidePanelAction::Make::make(PanelActionInitInfo init_info) {
		return new HidePanelAction{std::move(*this), init_info};
	}
	
	HidePanelAction::HidePanelAction(Make&& make, PanelActionInitInfo init_info) :
		PanelAction(init_info), only_on_parent_(make.only_on_parent), last_position_() {
	}
	
	auto HidePanelAction::update(sf::Vector2i point_position, bool active) -> void {
		last_position_ = sf::Vector2f{point_position};
		if(tracker_.update(active).stopped()) {
			if(
				only_on_parent_ ?
				panel_->get_parent_processed() :
				!panel_->in_panel(last_position_) && !panel_->in_const_panels(last_position_) && panel_->is_free()
				) {
				panel_manager_->hide_panel(panel_);
			}
		}
	}
}

auto ieml::Decode<char, ie::HidePanelAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::HidePanelAction::Make> {
	return {{node.get_as<bool>("only-on-parent").except().ok_or(false)}};
}
