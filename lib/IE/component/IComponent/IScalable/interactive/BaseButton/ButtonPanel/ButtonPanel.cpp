#include "ButtonPanel.hpp"

namespace ie {
	ButtonPanel::Make::Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelTrigger::Make>&& trigger, BoxPtr<IScalable::Make>&& background) :
		panel(std::move(panel)), trigger(std::move(trigger)), background(std::move(background)) {
	}
	
	auto ButtonPanel::Make::make(InitInfo init_info) -> ButtonPanel* {
		return new ButtonPanel{std::move(*this), init_info};
	}
	
	ButtonPanel::ButtonPanel(Make&& make, InitInfo init_info) :
		BaseButton(std::move(make.background), init_info),
		panel_(make.panel->make(init_info)),
		trigger_(make.trigger->make({init_info, *panel_})) {
	}
	
	auto ButtonPanel::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		BaseButton::resize(size, position);
		panel_->resize(size, position);
	}
	
	auto ButtonPanel::get_min_size() const -> sf::Vector2f {
		auto background_min_size{background_->get_min_size()};
		auto panel_min_size{panel_->get_min_size()};
		return {std::max(background_min_size.x, panel_min_size.x), std::max(background_min_size.y, panel_min_size.y)};
	}
	
	auto ButtonPanel::get_panel() const -> const Panel& {
		return *panel_;
	}
	
	auto ButtonPanel::update() -> void {
		trigger_->update();
	}
	
	auto ButtonPanel::handle_event(Event event) -> bool {
		return trigger_->handle_event(event) || BaseButton::handle_event(event);
	}
	
	auto ButtonPanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		BaseButton::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		panel_->draw_debug(render_target, 0, indent_addition, hue, hue_offset);
	}
}

auto ieml::Decode<char, ie::ButtonPanel::Make>::decode(ieml::Node const& node) -> orl::Option<ie::ButtonPanel::Make> {
	auto map{node.get_map_view().except()};
	return ie::ButtonPanel::Make{
		map.at("panel").except().as<ie::BoxPtr<ie::Panel::Make> >().except(),
		map.at("display-trigger").except().as<ie::BoxPtr<ie::IDisplayPanelTrigger::Make> >().except(),
		map.at("background").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
	};
}
