#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IMovePanelInteraction.hpp"

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
		
		bool get_at_start() override;
		
		void move(sf::Vector2i mouse_position) override;
	
	protected:
		sf::Vector2f coefficient_;
		sf::Vector2f offset_;
		bool at_start_;
	};
}

template<>
struct ieml::Decode<char, ie::CoefficientMovePanelInteraction::Make> {
	static orl::Option<ie::CoefficientMovePanelInteraction::Make> decode(ieml::Node const& node);
};
