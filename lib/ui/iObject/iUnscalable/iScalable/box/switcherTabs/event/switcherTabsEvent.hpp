#pragma once

#include "ui/interaction/event/key/simple/keyEventSimple.hpp"
#include "modules/appendix/yaml-cpp/shared/value/general/sValue.hpp"

namespace ui {
	class BoxSwitcherTabs;
	
	class SwitcherTabsEvent : public KeyEvent_Simple{
	protected:
		PISint value;
		BoxSwitcherTabs* switcherTabs;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SwitcherTabsEvent(const PISint& value, BoxSwitcherTabs* switcherTabs);
		
		SwitcherTabsEvent* copy() override;
	};
}

#include "switcherTabsEvent.inl"
