#pragma once

#include "../BasePanelInteraction/BasePanelInteraction.hpp"

namespace ie {
	class IMovePanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> IMovePanelInteraction* override = 0;
		};
		
		virtual auto get_at_start() -> bool = 0;
		
		virtual auto move(sf::Vector2i offset) -> void = 0;
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
	};
}
