#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace ie {
	class Window;
	
	class DynBuffer;
	
	class KeyHandler;
	
	class DrawManager;
	
	class UpdateManager;
	
	class InteractionManager;
	
	class IPanelManager;
	
	struct InitInfo {
		sf::RenderWindow& window;
		sf::RenderTarget& render_target;
		DynBuffer& dyn_buffer;
		KeyHandler& key_handler;
		DrawManager& draw_manager;
		UpdateManager& update_manager;
		InteractionManager& interaction_manager;
		IPanelManager& panel_manager;
		
		InitInfo(
			sf::RenderWindow& window_,
			sf::RenderTarget& render_target_,
			DynBuffer& dyn_buffer,
			KeyHandler& key_handler_,
			DrawManager& draw_manager_,
			UpdateManager& update_manager_,
			InteractionManager& interaction_manager_,
			IPanelManager& panel_manager_
		);
		
		auto copy(sf::RenderWindow& window_) const -> InitInfo;
		
		auto copy(sf::RenderTarget& render_target_) const -> InitInfo;
		
		auto copy(DynBuffer& dyn_buffer_) const -> InitInfo;
		
		auto copy(KeyHandler& key_handler_) const -> InitInfo;
		
		auto copy(DrawManager& draw_manager_) const -> InitInfo;
		
		auto copy(UpdateManager& update_manager_) const -> InitInfo;
		
		auto copy(InteractionManager& interaction_manager_) const -> InitInfo;
		
		auto copy(IPanelManager& panel_manager_) const -> InitInfo;
	};
}
