#pragma once
#include "../general/panelInteraction.h"

namespace ui {
	class MovePanelInteraction : public virtual BasePanelInteraction {
	protected:
		bool atStart;
		
	public:
		explicit MovePanelInteraction(bool atStart = false);
		
		virtual void move(sf::Vector2i mousePosition) = 0;
		
		void  start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		MovePanelInteraction* copy() override = 0;
	};
}
