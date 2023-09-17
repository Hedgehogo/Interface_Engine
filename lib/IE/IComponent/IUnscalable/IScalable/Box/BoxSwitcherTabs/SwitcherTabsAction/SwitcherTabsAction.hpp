#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/Modules/yaml-cpp/shared/value/general/sValue.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public BasicBaseKeyAction<BoxSwitcherTabs&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxSwitcherTabs&>::Make {
			PISint value;
			
			Make(PISint value);
			
			SwitcherTabsAction* make(BasicActionInitInfo<BoxSwitcherTabs&> initInfo) override;
		};
		
		SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> initInfo);
		
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
