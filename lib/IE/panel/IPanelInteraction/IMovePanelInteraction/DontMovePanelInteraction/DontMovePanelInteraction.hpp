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
		
		auto get_at_start() -> bool override;
		
		auto move(sf::Vector2i) -> void override;
		
		auto start(sf::Vector2i) -> void override;
		
		auto update(sf::Vector2i) -> void override;
		
		auto set_panel(Panel&) -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::DontMovePanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::DontMovePanelInteraction::Make>;
};
