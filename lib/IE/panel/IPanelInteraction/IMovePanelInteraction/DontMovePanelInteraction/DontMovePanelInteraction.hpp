#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "../IMovePanelInteraction.hpp"

namespace ie {
	class DontMovePanelInteraction : public virtual IMovePanelInteraction {
	public:
		struct Make : public virtual IMovePanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> DontMovePanelInteraction* override;
		};
		
		DontMovePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		DontMovePanelInteraction() = default;
		
		auto set_panel(Panel&) -> void override;
		
		auto move(sf::Vector2i) -> void override;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::DontMovePanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::DontMovePanelInteraction::Make>;
};
