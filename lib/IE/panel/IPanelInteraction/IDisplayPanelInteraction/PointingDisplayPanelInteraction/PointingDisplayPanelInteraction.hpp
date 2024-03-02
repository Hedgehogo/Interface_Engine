#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IDisplayPanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"

namespace ie {
	class PointingDisplayPanelInteraction : public BasePanelInteraction, public virtual IDisplayPanelInteraction {
	public:
		struct Make : public virtual IDisplayPanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> PointingDisplayPanelInteraction* override;
		};
		
		PointingDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::PointingDisplayPanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::PointingDisplayPanelInteraction::Make>;
};
