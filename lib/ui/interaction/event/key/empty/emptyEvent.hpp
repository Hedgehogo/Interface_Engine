#pragma once

#include "../keyEvent.hpp"

namespace ui {
	class EmptyEvent : public KeyEvent {
	public:
		EmptyEvent();
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		EmptyEvent* copy() override;
	};
}
