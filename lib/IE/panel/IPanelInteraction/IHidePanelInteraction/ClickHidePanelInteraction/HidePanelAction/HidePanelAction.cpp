#include "HidePanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	HidePanelAction::Make::Make(bool only_on_parent) : only_on_parent(only_on_parent) {
	}
	
	HidePanelAction* HidePanelAction::Make::make(PanelActionInitInfo init_info) {
		return new HidePanelAction{std::move(*this), init_info};
	}
	
	HidePanelAction::HidePanelAction(Make&& make, PanelActionInitInfo init_info) :
		PanelAction(init_info), only_on_parent(make.only_on_parent) {
	}
	
	HidePanelAction::HidePanelAction(bool only_on_parent) : only_on_parent(only_on_parent) {
	}
	
	void HidePanelAction::start_pressed() {
	}
	
	void HidePanelAction::while_pressed() {
	}
	
	void HidePanelAction::stop_pressed() {
		sf::Vector2f point_position{static_cast<sf::Vector2f>(mouse_position_)};
		if(only_on_parent ? panel_->get_parent_processed() : !panel_->in_panel(point_position) && !panel_->in_const_panels(point_position) && panel_->is_free()) {
			panel_manager_->hide_panel(panel_);
		}
	}
	
	void HidePanelAction::while_not_pressed() {
	}
	
	HidePanelAction* HidePanelAction::copy() {
		return new HidePanelAction{*this};
	}
}

orl::Option<ie::HidePanelAction::Make> ieml::Decode<char, ie::HidePanelAction::Make>::decode(ieml::Node const& node) {
	return {{node.get_as<bool>("only-on-parent").ok_or(false)}};
}
