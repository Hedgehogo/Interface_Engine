#pragma once

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
		
		explicit ClickHidePanelInteraction(Key key, bool only_on_parent = false);
		
		ClickHidePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<ClickHidePanelInteraction> {
		static bool decode_pointer(const YAML::Node& node, ClickHidePanelInteraction*& click_hide_panel_interaction);
	};
}
