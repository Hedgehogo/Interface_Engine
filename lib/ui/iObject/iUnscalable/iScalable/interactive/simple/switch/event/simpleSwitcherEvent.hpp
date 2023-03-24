#pragma once

#include "../../../../../../../interaction/event/key/simple/keyEventSimple.hpp"

namespace ui {
	class SimpleSwitcher;
	
	class SimpleSwitcherEvent : public KeyEvent_Simple {
	protected:
		SimpleSwitcher* switcher;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SimpleSwitcherEvent(SimpleSwitcher& switcher);
		
		void setSwitcher(SimpleSwitcher& switcher);
		
		SimpleSwitcherEvent* copy() override;
	};
	
}