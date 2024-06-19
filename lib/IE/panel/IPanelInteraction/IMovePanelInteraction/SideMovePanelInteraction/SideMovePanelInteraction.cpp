#include "SideMovePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	SideMovePanelInteraction::Make::Make(float coefficient, float offset, bool horizontal, bool at_start) :
		coefficient(coefficient), offset(offset), horizontal(horizontal), at_start(at_start) {
	}
	
	auto SideMovePanelInteraction::Make::make(PanelActionInitInfo init_info) -> SideMovePanelInteraction* {
		return new SideMovePanelInteraction{std::move(*this), init_info};
	}
	
	SideMovePanelInteraction::SideMovePanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		panel_(&init_info.additional),
		panel_manager_(&init_info.panel_manager),
		coefficient_(make.coefficient),
		offset_(make.offset),
		horizontal_(make.horizontal),
		at_start_(make.at_start) {
	}
	
	auto SideMovePanelInteraction::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto SideMovePanelInteraction::get_at_start() -> bool {
		return at_start_;
	}
	
	auto SideMovePanelInteraction::move(sf::Vector2i offset) -> void {
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
}

auto ieml::Decode<char, ie::SideMovePanelInteraction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::SideMovePanelInteraction::Make> {
	auto map{node.get_map_view().except()};
	return ie::SideMovePanelInteraction::Make{
		map.at("coefficient").except().as<float>().except(),
		map.at("offset").except().as<float>().except(),
		map.at("horizontal").except().as<bool>().except(),
		map.get_as<bool>("at-start").except().ok_or(false),
	};
}
