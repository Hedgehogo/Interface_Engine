#pragma once

#include "IE/IComponent/Panel/IPanelInteraction/ClickPanelInteraction/PanelAction/PanelAction.hpp"
#include "../../../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class HidePanelAction : public PanelAction {
	public:
		HidePanelAction(bool onlyOnParent = false);
		
		HidePanelAction* copy() override;
	
	protected:
		void startPressed() override;
		
		void whilePressed() override;
		
		void stopPressed() override;
		
		void whileNotPressed() override;
		
		bool onlyOnParent;
	};
	
	template<>
	struct DecodePointer<HidePanelAction> {
		static bool decodePointer(const YAML::Node& node, HidePanelAction*& hidePanelAction);
	};
}
