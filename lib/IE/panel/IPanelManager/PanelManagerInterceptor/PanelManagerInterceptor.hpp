#pragma once

#include "../IPanelManager.hpp"

namespace ie {
	class PanelManagerInterceptor : public virtual IPanelManager {
	public:
		PanelManagerInterceptor(IPanelManager& panel_manager);
		
		PanelManagerInterceptor();
		
		void init(IPanelManager& panel_manager);
		
		void clear();
		
		bool is_free() override;
		
		bool in_const_panels(sf::Vector2f point_position) override;
		
		void add_panel(BasePanel* panel) override;
		
		void remove_panel(BasePanel* panel) override;
		
		void display_panel(BasePanel* panel) override;
		
		void hide_panel(BasePanel* panel) override;
		
		void draw() override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position, bool active) override;
	
	protected:
		IPanelManager* panel_manager;
		std::vector<BasePanel*> panels;
	};
}
