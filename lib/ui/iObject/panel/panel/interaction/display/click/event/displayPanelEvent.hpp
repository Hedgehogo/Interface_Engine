#pragma once
#include "../../../click/event/panelEvent.hpp"
#include "../../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class DisplayPanelEvent : public PanelEvent {
	protected:
		void startPressed() override;
		
		void whilePressed() override;
		
		void stopPressed() override;
		
		void whileNotPressed() override;
	
	public:
		DisplayPanelEvent* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, DisplayPanelEvent *&displayPanelEvent);
	
	template<>
	struct DecodePointer<DisplayPanelEvent> {
		static bool decodePointer(const YAML::Node &node, DisplayPanelEvent *&displayPanelEvent);
	};
}