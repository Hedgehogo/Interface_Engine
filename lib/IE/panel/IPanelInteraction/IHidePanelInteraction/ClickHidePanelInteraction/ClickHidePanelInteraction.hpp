#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../../IHidePanelInteraction/ClickHidePanelInteraction/HidePanelAction/HidePanelAction.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ie {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public virtual IHidePanelInteraction {
	public:
		struct Make : public virtual IHidePanelInteraction::Make {
			Key key;
			bool only_on_parent = false;
			
			Make(Key key, bool only_on_parent = false);
			
			auto make(PanelActionInitInfo init_info) -> ClickHidePanelInteraction* override;
		};
		
		ClickHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
	};
}

template<>
struct ieml::Decode<char, ie::ClickHidePanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ClickHidePanelInteraction::Make>;
};
