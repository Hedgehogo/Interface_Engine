#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "DisplayPanelAction/DisplayPanelAction.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ie {
	class ClickDisplayPanelInteraction : public ClickPanelInteraction, public virtual IDisplayPanelInteraction {
	public:
		struct Make : public virtual IDisplayPanelInteraction::Make {
			Key key;
			
			Make(Key key);
			
			ClickDisplayPanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		ClickDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		explicit ClickDisplayPanelInteraction(Key key);
		
		void start(sf::Vector2i) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		ClickDisplayPanelInteraction* copy() override;
	};
}

template<>
struct ieml::Decode<char, ie::ClickDisplayPanelInteraction::Make> {
	static orl::Option<ie::ClickDisplayPanelInteraction::Make> decode(ieml::Node const& node);
};
