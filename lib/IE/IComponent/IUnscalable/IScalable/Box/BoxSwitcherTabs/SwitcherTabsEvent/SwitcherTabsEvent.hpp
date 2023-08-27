#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "IE/Modules/yaml-cpp/shared/value/general/sValue.hpp"

namespace ui {
	class BoxSwitcherTabs;
	
	class SwitcherTabsEvent : public BaseKeyEvent {
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
