#pragma once
#include "../iInteraction.h"

namespace ui {
	class MouseInteraction : public virtual IInteraction {
	protected:
		ButtonEvent* leftMouseButton;
		ButtonEvent* rightMouseButton;
		
	public:
		MouseInteraction(ButtonEvent* leftMouseButton, ButtonEvent* rightMouseButton);
		
		~MouseInteraction() override;
		
		void setLeftButtonEvent(ButtonEvent* leftMouseButton);
		
		void setRightButtonEvent(ButtonEvent* rightMouseButton);
		
		bool update(sf::Vector2i mousePosition) override;
	};
}
