#pragma once
#include "../general/panelInteraction.hpp"

namespace ui {
	class MovePanelInteraction : public virtual BasePanelInteraction {
	protected:
		bool atStart;
		
	public:
		explicit MovePanelInteraction(bool atStart = false);
		
		virtual void move(sf::Vector2i mousePosition) = 0;
		
		void  start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		MovePanelInteraction* copy() override = 0;
	};
}
