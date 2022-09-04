#pragma once
#include "../iInteraction.hpp"

namespace ui {
	class MouseInteraction : public virtual IInteraction {
	protected:
		ButtonEvent* leftMouseButton;
		ButtonEvent* rightMouseButton;
		
	public:
		MouseInteraction(ButtonEvent* leftMouseButton, ButtonEvent* rightMouseButton);

		void setLeftButtonEvent(ButtonEvent* leftMouseButton);
		
		void setRightButtonEvent(ButtonEvent* rightMouseButton);
		
		bool update(sf::Vector2i mousePosition) override;
	};
}
