#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IDisplayPanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"

namespace ie {
	class PointingDisplayPanelInteraction : public BasePanelInteraction, public virtual IDisplayPanelInteraction {
	public:
		struct Make : public virtual IDisplayPanelInteraction::Make {
			PointingDisplayPanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		PointingDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
	};
}

template<>
struct ieml::Decode<char, ie::PointingDisplayPanelInteraction::Make> {
	static orl::Option<ie::PointingDisplayPanelInteraction::Make> decode(ieml::Node const& node);
};
