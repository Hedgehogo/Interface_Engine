#pragma once

#include "../IAction.hpp"
#include "IE/sfml-events/MouseWheel/MouseWheel.hpp"

namespace ie {
	class WheelAction : public virtual IAction {
	public:
		explicit WheelAction();
		
		virtual void update(sf::Vector2i mouse_position, int value) = 0;
		
		virtual WheelAction* copy() = 0;
	
	protected:
		bool active_;
	};
}