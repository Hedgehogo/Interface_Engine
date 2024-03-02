#include "WhileSwitchTabsAction.hpp"

namespace ie {
	WhileSwitchTabsAction::Make::Make(int step) : step(step) {
	}
	
	auto WhileSwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> WhileSwitchTabsAction* {
		return new WhileSwitchTabsAction{std::move(*this), init_info};
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		BaseSwitchTabsAction(init_info), size_(box_->get_array_size()), value_(box_->get_value()), step_(make.step) {
	}
	
	auto WhileSwitchTabsAction::start_pressed() -> void {
	}
	
	auto WhileSwitchTabsAction::stop_pressed() -> void {
		auto index_value{static_cast<int>(value_.get())};
		index_value += step_;
		index_value = (((index_value % size_) + size_) % size_);
		value_.set(index_value);
	}
	
	auto WhileSwitchTabsAction::while_pressed() -> void {
	}
	
	auto WhileSwitchTabsAction::while_not_pressed() -> void {
	}
}

auto ieml::Decode<char, ie::WhileSwitchTabsAction::Make>::decode(ieml::Node const&) -> orl::Option<ie::WhileSwitchTabsAction::Make> {
	return {{}};
}
