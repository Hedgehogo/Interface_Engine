#include "SideMovePanelTrigger.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	SideMovePanelTrigger::Make::Make(float coefficient, float offset, bool horizontal, bool at_start) :
		coefficient(coefficient), offset(offset), horizontal(horizontal), at_start(at_start) {
	}
	
	auto SideMovePanelTrigger::Make::make(PanelActionInitInfo init_info) -> SideMovePanelTrigger* {
		return new SideMovePanelTrigger{std::move(*this), init_info};
	}
	
	SideMovePanelTrigger::SideMovePanelTrigger(Make&& make, PanelActionInitInfo init_info) :
		panel_(&init_info.additional),
		panel_manager_(&init_info.panel_manager),
		event_handler_(&init_info.event_handler),
		tracker_(),
		active_(false),
		coefficient_(make.coefficient),
		offset_(make.offset),
		horizontal_(make.horizontal),
		at_start_(make.at_start) {
	}
	
	auto SideMovePanelTrigger::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto SideMovePanelTrigger::move(sf::Vector2i offset) -> void {
		auto panel_size{panel_->get_area_size()};
		auto panel_position{panel_->get_area_position()};
		auto point_position{sf::Vector2f{offset}};
		auto position{
			horizontal_ ?
			(point_position.x - panel_size.x * coefficient_ + offset_) :
			(point_position.y - panel_size.y * coefficient_ + offset_)
		};
		panel_->set_position((horizontal_ ? sf::Vector2f{position, panel_position.y} : sf::Vector2f{panel_position.x, position}));
	}
	
	auto SideMovePanelTrigger::start() -> void {
	}
	
	auto SideMovePanelTrigger::handle_event(Event event) -> bool {
		return tracker_.collect(*event_handler_, event);
	}
	
	auto SideMovePanelTrigger::update() -> void {
		active_ = tracker_.reset().map([this](event_system::Pointer pointer) {
			if(!(at_start_ && active_)) {
				move(pointer.position);
			}
			return true;
		}).some_or(false);
	}
	
	auto SideMovePanelTrigger::finish() -> void {
		active_ = false;
	}
}

auto ieml::Decode<char, ie::SideMovePanelTrigger::Make>::decode(ieml::Node const& node) -> orl::Option<ie::SideMovePanelTrigger::Make> {
	auto map{node.get_map_view().except()};
	return ie::SideMovePanelTrigger::Make{
		map.at("coefficient").except().as<float>().except(),
		map.at("offset").except().as<float>().except(),
		map.at("horizontal").except().as<bool>().except(),
		map.get_as<bool>("at-start").except().ok_or(false),
	};
}
