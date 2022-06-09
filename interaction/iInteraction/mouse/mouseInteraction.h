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
		
		bool update(sf::Vector2i mousePosition) override;
	};
}
