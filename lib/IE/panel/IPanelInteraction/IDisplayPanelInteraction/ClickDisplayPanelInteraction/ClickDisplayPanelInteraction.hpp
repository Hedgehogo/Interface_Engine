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
			
			auto make(PanelActionInitInfo init_info) -> ClickDisplayPanelInteraction* override;
		};
		
		ClickDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		auto start(sf::Vector2i) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::ClickDisplayPanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ClickDisplayPanelInteraction::Make>;
};
