#pragma once

#include "../../../ClickPanelInteraction/PanelEvent/PanelEvent.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class DisplayPanelEvent : public PanelEvent {
	public:
		DisplayPanelEvent* copy() override;
	
	protected:
		void startPressed() override;
		
		void whilePressed() override;
		
		void stopPressed() override;
		
		void whileNotPressed() override;
	};
	
	template<>
	struct DecodePointer<DisplayPanelEvent> {
		static bool decodePointer(const YAML::Node& node, DisplayPanelEvent*& displayPanelEvent);
	};
}