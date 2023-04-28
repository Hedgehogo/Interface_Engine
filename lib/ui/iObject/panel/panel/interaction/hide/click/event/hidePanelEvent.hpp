#pragma once
#include "../../../click/event/panelEvent.hpp"
#include "../../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class HidePanelEvent : public PanelEvent {
	protected:
		bool onlyOnParent;
		
		void startPressed() override;
		
		void whilePressed() override;
		
		void stopPressed() override;
		
		void whileNotPressed() override;
		
	public:
		HidePanelEvent(bool onlyOnParent = false);
		
		HidePanelEvent* copy() override;
	};
	
	
	template<>
	struct DecodePointer<HidePanelEvent> {
		static bool decodePointer(const YAML::Node &node, HidePanelEvent *&hidePanelEvent);
	};
}
