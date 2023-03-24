#pragma once
#include "../iInteraction.hpp"

namespace ui {
	class MouseInteraction : public virtual IInteraction {
	protected:
		KeyEvent* leftMouseButton;
		KeyEvent* rightMouseButton;
		
	public:
		MouseInteraction(KeyEvent* leftMouseButton, KeyEvent* rightMouseButton);

		void setLeftButtonEvent(KeyEvent* leftMouseButton);
		
		void setRightButtonEvent(KeyEvent* rightMouseButton);
		
		void update(sf::Vector2i mousePosition) override;
	};
}
