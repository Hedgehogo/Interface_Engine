#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class IMovePanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> IMovePanelInteraction* override = 0;
		};
		
		virtual auto move(sf::Vector2i offset) -> void = 0;
	};
}
