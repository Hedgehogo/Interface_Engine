#pragma once

#include <SFML/System/Vector2.hpp>
#include "IE/event/EventHandler/EventHandler.hpp"
#include "IE/trigger/ITrigger/ITrigger.hpp"

namespace ie {
	class Window;
	
	class BaseWindowResizer {
	public:
		virtual auto set_window(Window& window) -> void;
		
		virtual auto update(std::vector<Event> const& events, EventHandler& event_handler) -> bool = 0;
		
		virtual ~BaseWindowResizer() = default;
	
	protected:
		Window* window_;
	};
}