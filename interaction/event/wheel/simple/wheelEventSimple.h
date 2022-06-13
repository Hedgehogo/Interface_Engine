#pragma once
#include "../wheelEvent.h"

namespace ui {
	class WheelEvent_Simple : public WheelEvent {
	protected:
		virtual void startPressed(sf::Vector2i windowPosition, int value) = 0;
		
		virtual void stopPressed(sf::Vector2i windowPosition, int value) = 0;
		
		virtual void whilePressed(sf::Vector2i windowPosition, int value) = 0;
		
		virtual void notPressed(sf::Vector2i windowPosition, int value) = 0;
	
	public:
		explicit WheelEvent_Simple();
		
		void update(sf::Vector2i mousePosition, int value) override;
	};
}
