#pragma once
#include <vector>
#include "../../iUnscalable/iScalable/iScalable.h"
#include "../panel/basePanel.h"

namespace ui {
	class PanelManager {
	protected:
		std::vector<BasePanel *> panels;
		std::vector<BasePanel *> activePanels;
		
		void print();
		
		void printActive();
	
	public:
		explicit PanelManager(std::vector<BasePanel *> panels = std::vector<BasePanel *>{});
		
		bool isFree();
		
		bool inConstPanels(sf::Vector2f pointPosition);
		
		void addPanel(BasePanel *panel);
		
		void displayPanel(BasePanel *panel);
		
		void hidePanel(BasePanel *panel);
		
		void draw();
		
		void update();
		
		bool updateInteractions(sf::Vector2f mousePosition, bool active);
	};
}
