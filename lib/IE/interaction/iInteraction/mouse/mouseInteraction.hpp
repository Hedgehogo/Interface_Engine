#pragma once

#include "../iInteraction.hpp"

namespace ui {
	class IMouseInteraction : public virtual IInteraction {
	public:
		IMouseInteraction();
		
		virtual KeyEvent& getLeftButtonEvent() = 0;
		
		virtual const KeyEvent& getLeftButtonEvent() const = 0;
		
		virtual KeyEvent& getRightButtonEvent() = 0;
		
		virtual const KeyEvent& getRightButtonEvent() const = 0;
		
		void update(sf::Vector2i mousePosition) override;
	};
}
