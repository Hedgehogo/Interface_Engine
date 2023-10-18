#pragma once

#include "../BasePanelInteraction/BasePanelInteraction.hpp"

namespace ie {
	class IMovePanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			IMovePanelInteraction* make(PanelActionInitInfo init_info) override = 0;
		};
		
		virtual bool get_at_start() = 0;
		
		virtual void move(sf::Vector2i mouse_position) = 0;
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		IMovePanelInteraction* copy() override = 0;
	};
}
