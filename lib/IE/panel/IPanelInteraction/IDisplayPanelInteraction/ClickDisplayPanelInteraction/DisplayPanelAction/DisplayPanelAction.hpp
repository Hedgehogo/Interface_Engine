#pragma once

#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class DisplayPanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			DisplayPanelAction* make(PanelActionInitInfo initInfo) override;
		};
		
		DisplayPanelAction(Make&& make, PanelActionInitInfo initInfo);
		
		DisplayPanelAction() = default;
		
		DisplayPanelAction* copy() override;
	
	protected:
		void startPressed() override;
		
		void whilePressed() override;
		
		void stopPressed() override;
		
		void whileNotPressed() override;
	};
	
	template<>
	struct DecodePointer<DisplayPanelAction> {
		static bool decodePointer(const YAML::Node& node, DisplayPanelAction*& displayPanelAction);
	};
}