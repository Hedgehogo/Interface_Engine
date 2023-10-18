#pragma once

#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class DisplayPanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			DisplayPanelAction* make(PanelActionInitInfo init_info) override;
		};
		
		DisplayPanelAction(Make&& make, PanelActionInitInfo init_info);
		
		DisplayPanelAction() = default;
		
		DisplayPanelAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void while_pressed() override;
		
		void stop_pressed() override;
		
		void while_not_pressed() override;
	};
	
	template<>
	struct DecodePointer<DisplayPanelAction> {
		static bool decode_pointer(const YAML::Node& node, DisplayPanelAction*& display_panel_action);
	};
}