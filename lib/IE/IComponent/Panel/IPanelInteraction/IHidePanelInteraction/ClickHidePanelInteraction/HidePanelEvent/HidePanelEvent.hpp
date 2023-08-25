#pragma once

#include "../../../ClickPanelInteraction/PanelEvent/PanelEvent.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class HidePanelEvent : public PanelEvent {
	public:
		HidePanelEvent(bool onlyOnParent = false);
		
		HidePanelEvent* copy() override;
	
	protected:
		void startPressed() override;
		
		void whilePressed() override;
		
		void stopPressed() override;
		
		void whileNotPressed() override;
		
		bool onlyOnParent;
	};
	
	template<>
	struct DecodePointer<HidePanelEvent> {
		static bool decodePointer(const YAML::Node& node, HidePanelEvent*& hidePanelEvent);
	};
}
