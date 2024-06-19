#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IDisplayPanelInteraction.hpp"

namespace ie {
	class PointingDisplayPanelInteraction : public virtual IDisplayPanelInteraction {
	public:
		struct Make : public virtual IDisplayPanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> PointingDisplayPanelInteraction* override;
		};
		
		PointingDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void override;
		
		auto start(sf::Vector2i) -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update(sf::Vector2i) -> void override;
		
		auto finish(sf::Vector2i) -> void override;
		
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
	};
}

template<>
struct ieml::Decode<char, ie::PointingDisplayPanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::PointingDisplayPanelInteraction::Make>;
};
