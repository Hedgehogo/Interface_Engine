#pragma once

#include "../general/panelInteraction.hpp"

namespace ui {
	class IMovePanelInteraction : public virtual IPanelInteraction {
	public:
		explicit IMovePanelInteraction();
		
		virtual bool getAtStart() = 0;
		
		virtual void move(sf::Vector2i mousePosition) = 0;
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		IMovePanelInteraction* copy() override = 0;
	};
}