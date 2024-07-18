#include "CoefficientMovePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	CoefficientMovePanelInteraction::Make::Make(sf::Vector2f coefficient, sf::Vector2f offset, bool at_start) :
		coefficient(coefficient), offset(offset), at_start(at_start) {
	}
	
	auto CoefficientMovePanelInteraction::Make::make(PanelActionInitInfo init_info) -> CoefficientMovePanelInteraction* {
		return new CoefficientMovePanelInteraction{std::move(*this), init_info};
	}
	
	CoefficientMovePanelInteraction::CoefficientMovePanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		panel_(&init_info.additional),
		panel_manager_(&init_info.panel_manager),
		event_handler_(&init_info.event_handler),
		tracker_(),
		active_(false),
		coefficient_(make.coefficient),
		offset_(make.offset),
		at_start_(make.at_start) {
	}
	
	auto CoefficientMovePanelInteraction::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto CoefficientMovePanelInteraction::move(sf::Vector2i offset) -> void {
		auto panel_size{panel_->get_area_size()};
		auto point_position{sf::Vector2f{offset}};
		auto position{sf::Vector2f{
			point_position.x - panel_size.x * coefficient_.x + offset_.x,
			point_position.y - panel_size.y * coefficient_.y + offset_.y,
		}};
		panel_->set_position(position);
	}
	
	auto CoefficientMovePanelInteraction::start() -> void {
	}
	
	auto CoefficientMovePanelInteraction::handle_event(Event event) -> bool {
		return tracker_.collect(*event_handler_, event);
	}
	
	auto CoefficientMovePanelInteraction::update() -> void {
		active_ = tracker_.reset().map([this](event_system::Pointer pointer) {
			if(!(at_start_ && active_)) {
				move(pointer.position);
			}
			return true;
		}).some_or(false);
	}
	
	auto CoefficientMovePanelInteraction::finish() -> void {
		active_ = false;
	}
}

auto ieml::Decode<char, ie::CoefficientMovePanelInteraction::Make>::decode(
	ieml::Node const& node
) -> orl::Option<ie::CoefficientMovePanelInteraction::Make> {
	auto map{node.get_map_view().except()};
	return ie::CoefficientMovePanelInteraction::Make{
		map.at("coefficient").except().as<sf::Vector2f>().except(),
		map.at("offset").except().as<sf::Vector2f>().except(),
		map.get_as<bool>("at-start").except().ok_or(false),
	};
}
