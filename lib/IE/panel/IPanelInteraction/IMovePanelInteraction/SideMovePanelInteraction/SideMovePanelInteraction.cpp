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
		BasePanelInteraction(init_info), coefficient(make.coefficient), offset(make.offset), horizontal(make.horizontal), at_start(make.at_start) {
	}
	
	SideMovePanelInteraction::SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool at_start) :
		coefficient(coefficient), offset(offset), horizontal(horizontal), at_start(at_start) {
	}
	
	bool SideMovePanelInteraction::get_at_start() {
		return at_start;
	}
	
	void SideMovePanelInteraction::move(sf::Vector2i mouse_position) {
		sf::Vector2f panel_size{panel->get_area_size()};
		sf::Vector2f panel_position{panel->get_area_position()};
		sf::Vector2f point_position{static_cast<sf::Vector2f>(mouse_position)};
		float position = (horizontal ? (point_position.x - panel_size.x * coefficient + offset) : (point_position.y - panel_size.y * coefficient + offset));
		panel->set_position((horizontal ? sf::Vector2f{position, panel_position.y} : sf::Vector2f{panel_position.x, position}));
	}
	
	SideMovePanelInteraction* SideMovePanelInteraction::copy() {
		return new SideMovePanelInteraction{*this};
	}
	
	bool DecodePointer<SideMovePanelInteraction>::decode_pointer(const YAML::Node& node, SideMovePanelInteraction*& side_move_panel_interaction) {
		float coefficient;
		float offset;
		bool horizontal;
		bool at_start = false;
		
		node["coefficient"] >> coefficient;
		node["offset"] >> offset;
		node["horizontal"] >> horizontal;
		if(node["at-start"])
			node["at-start"] >> at_start;
		
		side_move_panel_interaction = new SideMovePanelInteraction{coefficient, offset, horizontal, at_start};
		return true;
	}
}