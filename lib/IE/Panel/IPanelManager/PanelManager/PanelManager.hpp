#pragma once

#include "../IPanelManager.hpp"

namespace ie {
	class PanelManager : public virtual IPanelManager {
	protected:
		void print();
		
		void printActive();
	
	public:
		explicit PanelManager(std::vector<BasePanel*> panels = std::vector<BasePanel*>{});
		
		std::size_t size();
		
		BasePanel& get(std::size_t index);
		
		bool isFree() override;
		
		bool inConstPanels(sf::Vector2f pointPosition) override;
		
		void addPanel(BasePanel* panel) override;
		
		void removePanel(BasePanel* panel) override;
		
		void displayPanel(BasePanel* panel) override;
		
		void hidePanel(BasePanel* panel) override;
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition, bool active) override;
	
	protected:
		std::vector<BasePanel*> panels;
		std::vector<BasePanel*> activePanels;
	};
}
