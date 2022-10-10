#pragma once
#include "../../../click/event/panelEvent.hpp"

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
}
