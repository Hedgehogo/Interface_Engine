#pragma once

#include "../IPanelManager.hpp"

namespace ie {
	class PanelManager : public virtual IPanelManager {
	protected:
		auto print() -> void;
		
		auto print_active() -> void;
	
	public:
		explicit PanelManager(std::vector<BasePanel*> panels = std::vector<BasePanel*>{});
		
		auto size() -> size_t;
		
		auto get(size_t index) -> BasePanel&;
		
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
		std::vector<BasePanel*> panels_;
		std::vector<BasePanel*> active_panels_;
	};
}
