#pragma once

#include "../IPanelManager.hpp"

namespace ui {
	class PanelManagerInterceptor : public IPanelManager {
	public:
		PanelManagerInterceptor(IPanelManager& panelManager);
		
		PanelManagerInterceptor();
		
		void init(IPanelManager& panelManager);
		
		void clear();
		
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
		IPanelManager* panelManager;
		std::vector<BasePanel*> panels;
	};
}
