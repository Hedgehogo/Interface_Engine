#include "DisplayPanelEvent.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	void DisplayPanelEvent::startPressed() {
	}
	
	void DisplayPanelEvent::whilePressed() {
	}
	
	void DisplayPanelEvent::stopPressed() {
		panelManager->displayPanel(panel);
	}
	
	void DisplayPanelEvent::whileNotPressed() {
	}
	
	DisplayPanelEvent* DisplayPanelEvent::copy() {
		return new DisplayPanelEvent{*this};
	}
	
	bool DecodePointer<DisplayPanelEvent>::decodePointer(const YAML::Node&, DisplayPanelEvent*& displayPanelEvent) {
		displayPanelEvent = new DisplayPanelEvent{};
		return false;
	}
}