#include "WhileSwitchTabsAction.hpp"

namespace ie {
	WhileSwitchTabsAction::Make::Make(int step) : step(step) {
	}
	
	auto WhileSwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> WhileSwitchTabsAction* {
		return new WhileSwitchTabsAction{std::move(*this), init_info};
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		BaseSwitchTabsAction(init_info),
		size_(box_->get_array_size()),
		step_(((make.step % size_) + size_) % size_),
		value_(box_->get_value()) {
	}
	
	auto WhileSwitchTabsAction::update(bool active) -> void {
		if(active) {
			value_.set((value_.get() + step_) % size_);
		}
	}
}

auto ieml::Decode<char, ie::WhileSwitchTabsAction::Make>::decode(ieml::Node const&) -> orl::Option<ie::WhileSwitchTabsAction::Make> {
	return {{}};
}
