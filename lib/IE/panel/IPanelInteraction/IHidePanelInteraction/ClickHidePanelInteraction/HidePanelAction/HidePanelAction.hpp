#pragma once

#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class HidePanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			bool only_on_parent = false;
			
			Make(bool only_on_parent = false);
			
			HidePanelAction* make(PanelActionInitInfo init_info) override;
		};
		
		HidePanelAction(Make&& make, PanelActionInitInfo init_info);
		
		HidePanelAction(bool only_on_parent = false);
		
		HidePanelAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void while_pressed() override;
		
		void stop_pressed() override;
		
		void while_not_pressed() override;
		
		bool only_on_parent;
	};
	
	template<>
	struct DecodePointer<HidePanelAction> {
		static bool decode_pointer(const YAML::Node& node, HidePanelAction*& hide_panel_action);
	};
}