#pragma once

#include "../IPanelManager.hpp"

namespace ie {
	class PanelManager : public virtual IPanelManager {
	protected:
		void print();
		
		void print_active();
	
	public:
		explicit PanelManager(std::vector<BasePanel*> panels = std::vector<BasePanel*>{});
		
		size_t size();
		
		BasePanel& get(size_t index);
		
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
		std::vector<BasePanel*> panels_;
		std::vector<BasePanel*> active_panels_;
	};
}
