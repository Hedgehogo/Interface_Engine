#pragma once

#include "../IPanelManager.hpp"

namespace ie {
	class PanelManagerInterceptor : public virtual IPanelManager {
	public:
		PanelManagerInterceptor(IPanelManager& panel_manager);
		
		auto clear() -> void;
		
		auto is_free() -> bool override;
		
		auto in_const_panels(sf::Vector2f point_position) -> bool override;
		
		auto add_panel(BasePanel* panel) -> void override;
		
		auto remove_panel(BasePanel* panel) -> void override;
		
		auto display_panel(BasePanel* panel) -> void override;
		
		auto hide_panel(BasePanel* panel) -> void override;
		
		auto draw() -> void override;
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position, bool active) -> bool override;
	
	protected:
		IPanelManager* panel_manager_;
		std::vector<BasePanel*> panels_;
	};
}
