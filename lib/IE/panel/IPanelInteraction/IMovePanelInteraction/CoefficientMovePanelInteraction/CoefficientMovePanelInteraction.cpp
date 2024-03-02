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
		BasePanelInteraction(init_info), coefficient_(make.coefficient), offset_(make.offset), at_start_(make.at_start) {
	}
	
	auto CoefficientMovePanelInteraction::get_at_start() -> bool {
		return at_start_;
	}
	
	auto CoefficientMovePanelInteraction::move(sf::Vector2i mouse_position) -> void {
		auto panel_size{panel_->get_area_size()};
		auto point_position{sf::Vector2f{mouse_position}};
		auto position{sf::Vector2f{
			point_position.x - panel_size.x * coefficient_.x + offset_.x,
			point_position.y - panel_size.y * coefficient_.y + offset_.y,
		}};
		panel_->set_position(position);
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
