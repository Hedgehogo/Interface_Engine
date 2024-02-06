#pragma once

#include "../BasePanel/BasePanel.hpp"

namespace ie {
	class IPanelManager : public IUpdatable, public IDrawable {
	public:
		virtual bool is_free() = 0;
		
		virtual bool in_const_panels(sf::Vector2f point_position) = 0;
		
		virtual void add_panel(BasePanel* panel) = 0;
		
		virtual void remove_panel(BasePanel* panel) = 0;
		
		virtual void display_panel(BasePanel* panel) = 0;
		
		virtual void hide_panel(BasePanel* panel) = 0;
		
		void draw() override = 0;
		
		void update() override = 0;
		
		virtual bool update_interactions(sf::Vector2f mouse_position, bool active) = 0;
		
		virtual ~IPanelManager() = default;
	};
}
