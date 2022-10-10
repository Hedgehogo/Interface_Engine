#pragma once
#include "../../../click/event/panelEvent.hpp"

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
	
	bool convertPointer(const YAML::Node &node, HidePanelEvent *&hidePanelEvent);
}
