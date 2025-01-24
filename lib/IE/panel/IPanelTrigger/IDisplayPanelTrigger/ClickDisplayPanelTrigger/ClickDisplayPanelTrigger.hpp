#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "DisplayPanelAction/DisplayPanelAction.hpp"
#include "../../ClickPanelTrigger/ClickPanelTrigger.hpp"

namespace ie {
	class ClickDisplayPanelTrigger : public ClickPanelTrigger, public virtual IDisplayPanelTrigger {
	public:
		struct Make : public virtual IDisplayPanelTrigger::Make {
			Key key;
			
			Make(Key key);
			
			auto make(PanelActionInitInfo init_info) -> ClickDisplayPanelTrigger* override;
		};
		
		ClickDisplayPanelTrigger(Make&& make, PanelActionInitInfo init_info);
		
		auto start() -> void override;
		
		auto finish() -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::ClickDisplayPanelTrigger::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ClickDisplayPanelTrigger::Make>;
};
