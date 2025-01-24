#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../../IHidePanelTrigger/ClickHidePanelTrigger/HidePanelAction/HidePanelAction.hpp"
#include "../../ClickPanelTrigger/ClickPanelTrigger.hpp"

namespace ie {
	class ClickHidePanelTrigger : public ClickPanelTrigger, public virtual IHidePanelTrigger {
	public:
		struct Make : public virtual IHidePanelTrigger::Make {
			Key key;
			bool only_on_parent = false;
			
			Make(Key key, bool only_on_parent = false);
			
			auto make(PanelActionInitInfo init_info) -> ClickHidePanelTrigger* override;
		};
		
		ClickHidePanelTrigger(Make&& make, PanelActionInitInfo init_info);
	};
}

template<>
struct ieml::Decode<char, ie::ClickHidePanelTrigger::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ClickHidePanelTrigger::Make>;
};
