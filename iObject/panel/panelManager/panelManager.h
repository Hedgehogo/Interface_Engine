#pragma once
#include <vector>
#include "../../iFlat/iFlat.h"
#include "../panel.h"

namespace ui {
	class PanelManager {
	protected:
		std::vector<Panel *> panels;
		std::vector<Panel *> activePanels;
	
	public:
		explicit PanelManager(std::vector<Panel *> panels = std::vector<Panel *>{});
		
		void addPanel(Panel *panel);
		
		void displayPanel(Panel *panel);
		
		void hidePanel(Panel *panel);
		
		void update();
		
		void draw();
		
		void updateInteractions(sf::Vector2f mousePosition);
	};
}
