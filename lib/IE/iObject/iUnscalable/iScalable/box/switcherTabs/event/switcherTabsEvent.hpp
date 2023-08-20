#pragma once

#include "IE/interaction/event/key/simple/keyEventSimple.hpp"
#include "modules/appendix/yaml-cpp/shared/value/general/sValue.hpp"

namespace ui {
	class BoxSwitcherTabs;
	
	class SwitcherTabsEvent : public KeyEvent_Simple {
	public:
		SwitcherTabsEvent(PISint value, BoxSwitcherTabs& switcherTabs);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		SwitcherTabsEvent* copy() override;
	
	protected:
		PISint value;
		BoxSwitcherTabs* switcherTabs;
	};
}
