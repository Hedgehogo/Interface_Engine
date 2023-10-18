#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace ie {
	class Window;
	
	class DrawManager;
	
	class UpdateManager;
	
	class InteractionManager;
	
	class InteractionStack;
	
	class IPanelManager;
	
	struct InitInfo {
		sf::RenderWindow& window;
		sf::RenderTarget& render_target;
		DrawManager& draw_manager;
		UpdateManager& update_manager;
		InteractionManager& interaction_manager;
		InteractionStack& interaction_stack;
		IPanelManager& panel_manager;
		
		InitInfo(sf::RenderWindow& window_, sf::RenderTarget& render_target_, DrawManager& draw_manager_, UpdateManager& update_manager_, InteractionManager& interaction_manager_, InteractionStack& interaction_stack_, IPanelManager& panel_manager_);
		
		InitInfo copy(sf::RenderWindow& window_) const;
		
		InitInfo copy(sf::RenderTarget& render_target_) const;
		
		InitInfo copy(DrawManager& draw_manager_) const;
		
		InitInfo copy(UpdateManager& update_manager_) const;
		
		InitInfo copy(InteractionManager& interaction_manager_) const;
		
		InitInfo copy(InteractionStack& interaction_stack_) const;
		
		InitInfo copy(IPanelManager& panel_manager_) const;
	};
}
