#pragma once

#include "../BasePanel/BasePanel.hpp"

namespace ie {
	class IPanelManager : public IUpdatable, public IDrawable {
	public:
		virtual auto is_free() -> bool = 0;
		
		virtual auto in_const_panels(sf::Vector2f point_position) -> bool = 0;
		
		virtual auto add_panel(BasePanel* panel) -> void = 0;
		
		virtual auto remove_panel(BasePanel* panel) -> void = 0;
		
		virtual auto display_panel(BasePanel* panel) -> void = 0;
		
		virtual auto hide_panel(BasePanel* panel) -> void = 0;
		
		auto draw() -> void override = 0;
		
		auto update() -> void override = 0;
		
		virtual auto update_interactions(sf::Vector2f mouse_position, bool active) -> bool = 0;
		
		virtual ~IPanelManager() = default;
	};
}
