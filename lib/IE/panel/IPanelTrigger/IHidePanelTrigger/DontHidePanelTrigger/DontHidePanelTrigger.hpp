#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/trigger/ITrigger/BasicEmptyTrigger/BasicEmptyTrigger.hpp"
#include "../IHidePanelTrigger.hpp"

namespace ie {
	class DontHidePanelTrigger : public BasicEmptyTrigger<Panel&>, public virtual IHidePanelTrigger {
	public:
		struct Make : public virtual IHidePanelTrigger::Make {
			auto make(PanelActionInitInfo init_info) -> DontHidePanelTrigger* override;
		};
		
		DontHidePanelTrigger(Make&& make, PanelActionInitInfo init_info);
		
		DontHidePanelTrigger() = default;
		
		auto set_panel(Panel&) -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::DontHidePanelTrigger::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::DontHidePanelTrigger::Make>;
};
