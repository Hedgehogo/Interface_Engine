#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IHidePanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"

namespace ie {
	class PointingHidePanelInteraction : public BasePanelInteraction, public virtual IHidePanelInteraction {
	public:
		struct Make : public virtual IHidePanelInteraction::Make {
			bool only_on_parent = false;
			
			Make(bool only_on_parent = false);
			
			PointingHidePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		PointingHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		PointingHidePanelInteraction(bool only_on_parent = false);
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		PointingHidePanelInteraction* copy() override;
	
	protected:
		bool only_on_parent_;
	};
}

template<>
struct ieml::Decode<char, ie::PointingHidePanelInteraction::Make> {
	static orl::Option<ie::PointingHidePanelInteraction::Make> decode(ieml::Node const& node);
};
