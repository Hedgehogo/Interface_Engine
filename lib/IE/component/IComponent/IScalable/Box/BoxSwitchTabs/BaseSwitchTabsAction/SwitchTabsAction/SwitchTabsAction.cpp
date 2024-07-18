#include "SwitchTabsAction.hpp"

namespace ie {
	SwitchTabsAction::Make::Make(size_t index) : index(index) {
	}
	
	auto SwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> init_info) -> SwitchTabsAction* {
		return new SwitchTabsAction{std::move(*this), init_info};
	}
	
	SwitchTabsAction::SwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> init_info) :
		BaseSwitchTabsAction(init_info), index_(make.index), value_(box_->get_value()) {
	}
	
	auto SwitchTabsAction::update(bool active) -> void {
		if(active) {
			value_.set(index_);
		}
	}
}

auto ieml::Decode<char, ie::SwitchTabsAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::SwitchTabsAction::Make> {
	return {{node.get_as<size_t>("index").except().ok_or(0u)}};
}