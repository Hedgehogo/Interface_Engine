#pragma once

#include "../IMovePanelInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class CoefficientMovePanelInteraction : public BasePanelInteraction, public virtual IMovePanelInteraction {
	public:
		struct Make : public virtual IMovePanelInteraction::Make {
			sf::Vector2f coefficient;
			sf::Vector2f offset;
			bool at_start = false;
			
			Make(sf::Vector2f coefficient, sf::Vector2f offset, bool at_start = false);
			
			CoefficientMovePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		CoefficientMovePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		CoefficientMovePanelInteraction(sf::Vector2f coefficient, sf::Vector2f offset, bool at_start = false);
		
		bool get_at_start() override;
		
		void move(sf::Vector2i mouse_position) override;
		
		CoefficientMovePanelInteraction* copy() override;
	
	protected:
		sf::Vector2f coefficient;
		sf::Vector2f offset;
		bool at_start;
	};
	
	template<>
	struct DecodePointer<CoefficientMovePanelInteraction> {
		static bool decode_pointer(const YAML::Node& node, CoefficientMovePanelInteraction*& coefficient_move_panel_interaction);
	};
}