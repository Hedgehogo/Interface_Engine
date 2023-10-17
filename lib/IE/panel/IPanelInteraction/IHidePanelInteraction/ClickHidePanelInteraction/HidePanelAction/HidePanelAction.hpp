#pragma once

#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class HidePanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			bool onlyOnParent = false;
			
			Make(bool onlyOnParent = false);
			
			HidePanelAction* make(PanelActionInitInfo initInfo) override;
		};
		
		HidePanelAction(Make&& make, PanelActionInitInfo initInfo);
		
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