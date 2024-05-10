#include "SwitcherTabsAction.hpp"
#include "../BoxSwitcherTabs.hpp"

namespace ie {
	SwitcherTabsAction::Make::Make(MakeDyn<ISMRSize> value) : value(std::move(value)) {
	}
	
	auto SwitcherTabsAction::Make::make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) -> SwitcherTabsAction* {
		return new SwitcherTabsAction{std::move(*this), init_info};
	}
	
	SwitcherTabsAction::SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info) :
		value_(make.value.make(SInitInfo{init_info})), switcher_tabs_(&init_info.additional) {
	}
	
	auto SwitcherTabsAction::update(sf::Vector2i point_position, bool active) -> void {
		if(tracker_.update(active).stopped()) {
			value_.set(switcher_tabs_->get_tab(sf::Vector2f{point_position}));
		}
	}
}