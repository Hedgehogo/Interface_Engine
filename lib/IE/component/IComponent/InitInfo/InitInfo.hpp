#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <absl/container/flat_hash_set.h>
#include <box-ptr/BoxPtr.hpp>

namespace ie {
	class Window;
	
	class DynBuffer;
	
	class EventHandler;
	
	class DrawManager;
	
	class UpdateManager;
	
	class TriggerManager;
	
	class IPanelManager;
	
	template<typename T_>
	class Indexed;
	
	struct TextStyle;
	
	struct InitInfo {
		sf::RenderWindow& window;
		sf::RenderTarget& render_target;
		DynBuffer& dyn_buffer;
		absl::flat_hash_set<Indexed<TextStyle> >& text_style_buffer;
		EventHandler& event_handler;
		DrawManager& draw_manager;
		UpdateManager& update_manager;
		TriggerManager& trigger_manager;
		IPanelManager& panel_manager;
		
		InitInfo(
			sf::RenderWindow& window_,
			sf::RenderTarget& render_target_,
			DynBuffer& dyn_buffer_,
			absl::flat_hash_set<Indexed<TextStyle> >& text_style_buffer_,
			EventHandler& event_handler_,
			DrawManager& draw_manager_,
			UpdateManager& update_manager_,
			TriggerManager& trigger_manager_,
			IPanelManager& panel_manager_
		);
		
		auto copy(sf::RenderWindow& window_) const -> InitInfo;
		
		auto copy(sf::RenderTarget& render_target_) const -> InitInfo;
		
		auto copy(DynBuffer& dyn_buffer_) const -> InitInfo;
		
		auto copy(absl::flat_hash_set<Indexed<TextStyle> >& text_style_buffer_) const -> InitInfo;
		
		auto copy(EventHandler& event_handler_) const -> InitInfo;
		
		auto copy(DrawManager& draw_manager_) const -> InitInfo;
		
		auto copy(UpdateManager& update_manager_) const -> InitInfo;
		
		auto copy(TriggerManager& trigger_manager_) const -> InitInfo;
		
		auto copy(IPanelManager& panel_manager_) const -> InitInfo;
	};
}
