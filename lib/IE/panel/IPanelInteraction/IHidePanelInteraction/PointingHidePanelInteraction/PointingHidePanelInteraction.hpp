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
			
			auto make(PanelActionInitInfo init_info) -> PointingHidePanelInteraction* override;
		};
		
		PointingHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
		
	protected:
		bool only_on_parent_;
	};
}

template<>
struct ieml::Decode<char, ie::PointingHidePanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::PointingHidePanelInteraction::Make>;
};
