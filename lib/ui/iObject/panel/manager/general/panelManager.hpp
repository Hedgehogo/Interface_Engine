#pragma once

#include "../iPanelManager.hpp"

namespace ui {
	class PanelManager : public IPanelManager {
	protected:
		std::vector<BasePanel*> panels;
		std::vector<BasePanel*> activePanels;
		
		void print();
		
		void printActive();
	
	public:
		explicit PanelManager(std::vector<BasePanel*> panels = std::vector<BasePanel*>{});
		
		bool isFree() override;
		
		bool inConstPanels(sf::Vector2f pointPosition) override;
		
		void addPanel(BasePanel* panel) override;
		
		void removePanel(BasePanel* panel) override;
		
		void displayPanel(BasePanel* panel) override;
		
		void hidePanel(BasePanel* panel) override;
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition, bool active) override;
	};
}
