#include "CoefficientMovePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	CoefficientMovePanelInteraction::Make::Make(sf::Vector2f coefficient, sf::Vector2f offset, bool at_start) :
		coefficient(coefficient), offset(offset), at_start(at_start) {
	}
	
	CoefficientMovePanelInteraction* CoefficientMovePanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new CoefficientMovePanelInteraction{std::move(*this), init_info};
	}
	
	CoefficientMovePanelInteraction::CoefficientMovePanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		BasePanelInteraction(init_info), coefficient_(make.coefficient), offset_(make.offset), at_start_(make.at_start) {
	}
	
	CoefficientMovePanelInteraction::CoefficientMovePanelInteraction(sf::Vector2f coefficient, sf::Vector2f offset, bool at_start) :
		coefficient_(coefficient), offset_(offset), at_start_(at_start) {
	}
	
	bool CoefficientMovePanelInteraction::get_at_start() {
		return at_start_;
	}
	
	void CoefficientMovePanelInteraction::move(sf::Vector2i mouse_position) {
		sf::Vector2f panel_size{panel_->get_area_size()};
		sf::Vector2f point_position{static_cast<sf::Vector2f>(mouse_position)};
		panel_->set_position({point_position.x - panel_size.x * coefficient_.x + offset_.x, point_position.y - panel_size.y * coefficient_.y + offset_.y});
	}
	
	CoefficientMovePanelInteraction* CoefficientMovePanelInteraction::copy() {
		return new CoefficientMovePanelInteraction{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<CoefficientMovePanelInteraction>::decode_pointer(const YAML::Node& node, CoefficientMovePanelInteraction*& coefficient_move_panel_interaction) {
		sf::Vector2f coefficient;
		sf::Vector2f offset;
		bool at_start{false};
		
		node["coefficient"] >> coefficient;
		node["offset"] >> offset;
		if(node["at-start"])
			node["at-start"] >> at_start;
		
		coefficient_move_panel_interaction = new CoefficientMovePanelInteraction{coefficient, offset, at_start};
		return true;

	}
	*/
}