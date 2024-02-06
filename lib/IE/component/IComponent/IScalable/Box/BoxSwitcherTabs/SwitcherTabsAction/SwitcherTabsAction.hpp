#pragma once

#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BoxSwitcherTabs;
	
	class SwitcherTabsAction : public BasicBaseKeyAction<BoxSwitcherTabs&> {
	public:
		struct Make : public virtual BasicKeyAction<BoxSwitcherTabs&>::Make {
			MakeDyn<ISMRSize> value;
			
			Make(MakeDyn<ISMRSize> value);
			
			SwitcherTabsAction* make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) override;
		};
		
		SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info);
		
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
	protected:
		ISMRSize& value_;
		BoxSwitcherTabs* switcher_tabs_;
	};
}