#pragma once

#include "../IAction.hpp"
#include "IE/event/MouseWheel/MouseWheel.hpp"

namespace ie {
	class WheelAction : public virtual IAction {
	public:
		explicit WheelAction();
		
		virtual auto update(sf::Vector2i mouse_position, int value) -> void = 0;
		
	protected:
		bool active_;
	};
}