#include "SwitcherTabsAction.hpp"
#include "../BoxSwitcherTabs.hpp"

namespace ie {
	SwitcherTabsAction::Make::Make(MakeDyn<ISMRSize> value) : value(std::move(value)) {
	}
	
	auto SwitcherTabsAction::Make::make(BasicActionInitInfo<BoxSwitcherTabs&> init_info) -> SwitcherTabsAction* {
		return new SwitcherTabsAction{std::move(*this), init_info};
	}
	
	SwitcherTabsAction::SwitcherTabsAction(Make&& make, BasicActionInitInfo<BoxSwitcherTabs&> init_info) :
		pressing(), value_(make.value.make(SInitInfo{init_info})), switcher_tabs_(&init_info.additional) {
	}
	
	auto SwitcherTabsAction::update(orl::Option<Touch> touch) -> void {
		pressing = touch.and_then([](Touch value) -> orl::Option<orl::Option<sf::Vector2f> > {
			return value.active && orl::Option{sf::Vector2f{value.position}};
		}).some_or_else([this] {
			for(auto point_position: pressing) {
				value_.set(switcher_tabs_->get_tab(point_position));
			}
			return orl::Option<sf::Vector2f>{};
		});
	}
}