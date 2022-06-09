#pragma once
#include <vector>
#include "../../iFlat/iFlat.h"
#include "../panel.h"

namespace ui {
	class PanelStack {
	protected:
		std::vector<Panel *> panels;
	
	public:
		explicit PanelStack(std::vector<Panel *> panels = std::vector<Panel *>{});
		
		void displayPanel(Panel *panel);
		
		void hidePanel(Panel *panel);
		
		void update();
		
		void draw();
		
		void updateInteractions(sf::Vector2f mousePosition);
	};
}
