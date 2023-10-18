#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/shared/ISValue/SValue/SValue.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public BasicBaseKeyAction<BoxSwitcherTabs&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxSwitcherTabs&>::Make {
			PISint value;
			
			Make(PISint value);
			
			SwitcherTabsAction* make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) override;
		};
		
		SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info);
		
		SwitcherTabsAction(PISint value);
		
		void init(BasicActionInitInfo<BoxSwitcherTabs&> init_info) override;
		
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		SwitcherTabsAction* copy() override;
	
	protected:
		PISint value;
		BoxSwitcherTabs* switcher_tabs;
	};
}