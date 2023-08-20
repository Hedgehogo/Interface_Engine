#pragma once

#include "../../../../../../../Interaction/IEvent/KeyEvent/BaseKeyEvent/BaseKeyEvent.hpp"

namespace ui {
	class BoxWithMovableBorder;
	
	class MovableBorderEvent : public BaseKeyEvent {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit MovableBorderEvent(BoxWithMovableBorder& box);
		
		void setBox(BoxWithMovableBorder& box);
		
		MovableBorderEvent* copy() override;
	
	protected:
		BoxWithMovableBorder* box;
		sf::Vector2i startMousePosition;
		float startBorderValue;
		bool active;
	};
}



