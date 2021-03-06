#pragma once
#include "../buttonEvent.h"

namespace ui {
	class EmptyEvent : public ButtonEvent {
	public:
		EmptyEvent();
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		EmptyEvent* copy() override;
	};
}
