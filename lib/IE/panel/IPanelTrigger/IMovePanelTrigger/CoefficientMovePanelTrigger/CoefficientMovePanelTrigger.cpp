#include "CoefficientMovePanelTrigger.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	CoefficientMovePanelTrigger::Make::Make(sf::Vector2f coefficient, sf::Vector2f offset, bool at_start) :
		coefficient(coefficient), offset(offset), at_start(at_start) {
	}
	
	auto CoefficientMovePanelTrigger::Make::make(PanelActionInitInfo init_info) -> CoefficientMovePanelTrigger* {
		return new CoefficientMovePanelTrigger{std::move(*this), init_info};
	}
	
	CoefficientMovePanelTrigger::CoefficientMovePanelTrigger(Make&& make, PanelActionInitInfo init_info) :
		panel_(&init_info.additional),
		panel_manager_(&init_info.panel_manager),
		event_handler_(&init_info.event_handler),
		tracker_(),
		active_(false),
		coefficient_(make.coefficient),
		offset_(make.offset),
		at_start_(make.at_start) {
	}
	
	auto CoefficientMovePanelTrigger::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto CoefficientMovePanelTrigger::move(sf::Vector2i offset) -> void {
		auto panel_size{panel_->get_area_size()};
		auto point_position{sf::Vector2f{offset}};
		auto position{sf::Vector2f{
			point_position.x - panel_size.x * coefficient_.x + offset_.x,
			point_position.y - panel_size.y * coefficient_.y + offset_.y,
		}};
		panel_->set_position(position);
	}
	
	auto CoefficientMovePanelTrigger::start() -> void {
	}
	
	auto CoefficientMovePanelTrigger::handle_event(Event event) -> bool {
		return tracker_.collect(*event_handler_, event);
	}
	
	auto CoefficientMovePanelTrigger::update() -> void {
		active_ = tracker_.reset().map([this](event_system::Pointer pointer) {
			if(!(at_start_ && active_)) {
				move(pointer.position);
			}
			return true;
		}).some_or(false);
	}
	
	auto CoefficientMovePanelTrigger::finish() -> void {
		active_ = false;
	}
}

auto ieml::Decode<char, ie::CoefficientMovePanelTrigger::Make>::decode(
	ieml::Node const& node
) -> orl::Option<ie::CoefficientMovePanelTrigger::Make> {
	auto map{node.get_map_view().except()};
	return ie::CoefficientMovePanelTrigger::Make{
		map.at("coefficient").except().as<sf::Vector2f>().except(),
		map.at("offset").except().as<sf::Vector2f>().except(),
		map.get_as<bool>("at-start").except().ok_or(false),
	};
}
