#include "SideMovePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	SideMovePanelInteraction::Make::Make(float coefficient, float offset, bool horizontal, bool at_start) :
		coefficient(coefficient), offset(offset), horizontal(horizontal), at_start(at_start) {
	}
	
	SideMovePanelInteraction* SideMovePanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new SideMovePanelInteraction{std::move(*this), init_info};
	}
	
	SideMovePanelInteraction::SideMovePanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		BasePanelInteraction(init_info), coefficient_(make.coefficient), offset_(make.offset), horizontal_(make.horizontal), at_start_(make.at_start) {
	}
	
	SideMovePanelInteraction::SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool at_start) :
		coefficient_(coefficient), offset_(offset), horizontal_(horizontal), at_start_(at_start) {
	}
	
	bool SideMovePanelInteraction::get_at_start() {
		return at_start_;
	}
	
	void SideMovePanelInteraction::move(sf::Vector2i mouse_position) {
		sf::Vector2f panel_size{panel_->get_area_size()};
		sf::Vector2f panel_position{panel_->get_area_position()};
		sf::Vector2f point_position{static_cast<sf::Vector2f>(mouse_position)};
		float position = (horizontal_ ? (point_position.x - panel_size.x * coefficient_ + offset_) : (point_position.y - panel_size.y * coefficient_ + offset_));
		panel_->set_position((horizontal_ ? sf::Vector2f{position, panel_position.y} : sf::Vector2f{panel_position.x, position}));
	}
	
	SideMovePanelInteraction* SideMovePanelInteraction::copy() {
		return new SideMovePanelInteraction{*this};
	}
}

orl::Option<ie::SideMovePanelInteraction::Make> ieml::Decode<char, ie::SideMovePanelInteraction::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::SideMovePanelInteraction::Make{
		map.at("coefficient").except().as<float>().except(),
		map.at("offset").except().as<float>().except(),
		map.at("horizontal").except().as<bool>().except(),
		map.get_as<bool>("at-start").ok_or(false),
	};
}
