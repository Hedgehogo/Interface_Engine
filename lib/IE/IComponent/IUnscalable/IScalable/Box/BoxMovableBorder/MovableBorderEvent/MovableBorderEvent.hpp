#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"

namespace ui {
	class BoxMovableBorder;
	
	class MovableBorderEvent : public BaseKeyEvent {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit MovableBorderEvent(BoxMovableBorder& box);
		
		void setBox(BoxMovableBorder& box);
		
		MovableBorderEvent* copy() override;
	
	protected:
		BoxMovableBorder* box;
		sf::Vector2i startMousePosition;
		float startBorderValue;
		bool active;
	};
}



