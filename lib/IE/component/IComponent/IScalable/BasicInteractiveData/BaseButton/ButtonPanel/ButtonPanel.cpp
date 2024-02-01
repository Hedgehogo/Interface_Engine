#include "ButtonPanel.hpp"

namespace ie {
	ButtonPanel::Make::Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelInteraction::Make>&& interaction, BoxPtr<IScalable::Make>&& background) :
		panel(std::move(panel)), interaction(std::move(interaction)), background(std::move(background)) {
	}
	
	ButtonPanel* ButtonPanel::Make::make(InitInfo init_info) {
		return new ButtonPanel{std::move(*this), init_info};
	}
	
	ButtonPanel::ButtonPanel(Make&& make, InitInfo init_info) :
		BaseButton(std::move(make.background), init_info),
		panel_(make.panel->make(init_info)),
		interactive_(std::move(make.interaction), init_info, *panel_) {
	}
	
	void ButtonPanel::resize(sf::Vector2f size, sf::Vector2f position) {
		BaseButton::resize(size, position);
		panel_->resize(size, position);
	}
	
	sf::Vector2f ButtonPanel::get_min_size() const {
		sf::Vector2f background_min_size{background_->get_min_size()};
		sf::Vector2f panel_min_size{panel_->get_min_size()};
		return {std::max(background_min_size.x, panel_min_size.x), std::max(background_min_size.y, panel_min_size.y)};
	}
	
	const Panel& ButtonPanel::get_panel() const {
		return *panel_;
	}
	
	void ButtonPanel::update() {
		interactive_.update();
	}
	
	bool ButtonPanel::update_interactions(sf::Vector2f mouse_position) {
		bool result{BaseButton::update_interactions(mouse_position)};
		interactive_.update_interactions();
		return result;
	}
	
	void ButtonPanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		BaseButton::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		panel_->draw_debug(render_target, 0, indent_addition, hue, hue_offset);
	}
}

orl::Option<ie::ButtonPanel::Make> ieml::Decode<char, ie::ButtonPanel::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::ButtonPanel::Make{
		map.at("panel").except().as<ie::BoxPtr<ie::Panel::Make> >().move_except(),
		map.at("display-interaction").except().as<ie::BoxPtr<ie::IDisplayPanelInteraction::Make> >().move_except(),
		map.at("background").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
	};
}
