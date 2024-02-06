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
			
			ClickHidePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		ClickHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
	};
}

template<>
struct ieml::Decode<char, ie::ClickHidePanelInteraction::Make> {
	static orl::Option<ie::ClickHidePanelInteraction::Make> decode(ieml::Node const& node);
};
