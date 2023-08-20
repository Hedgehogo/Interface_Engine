#pragma once

#include <SFML/System/Vector2.hpp>
#include "../IEvent.hpp"
#include "../../InteractionInitInfo/InteractionInitInfo.hpp"

namespace ui {
	class KeyEvent : public IEvent {
	public:
		explicit KeyEvent();
		
		virtual void init(InteractionInitInfo);
		
		virtual void setPressed(bool pressed);
		
		virtual void update(sf::Vector2i mousePosition, bool press) = 0;
		
		virtual KeyEvent* copy() = 0;
	
	protected:
		bool pressed;
	};
}
