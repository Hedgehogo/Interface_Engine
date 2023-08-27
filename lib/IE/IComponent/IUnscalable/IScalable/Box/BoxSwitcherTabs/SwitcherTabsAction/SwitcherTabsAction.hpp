#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/Modules/yaml-cpp/shared/value/general/sValue.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public BasicBaseKeyAction<BoxSwitcherTabs&> {
	public:
		SwitcherTabsAction(PISint value);
		
		void init(BasicActionInitInfo<BoxSwitcherTabs&> initInfo) override;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		SwitcherTabsAction* copy() override;
	
	protected:
		PISint value;
		BoxSwitcherTabs* switcherTabs;
	};
}
