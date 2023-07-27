#include "closeWindowEvent.hpp"

#include "ui/window/window.hpp"

namespace ui {
	CloseWindowEvent::CloseWindowEvent() : window{nullptr}{
	}
	
	void CloseWindowEvent::startPressed() {
	
	}
	
	void CloseWindowEvent::stopPressed() {
		window->close();
	}
	
	void CloseWindowEvent::whilePressed() {
	
	}
	
	void CloseWindowEvent::whileNotPressed() {
	
	}
	
	void CloseWindowEvent::copy(CloseWindowEvent* closeWindow) {
		closeWindow->window = window;
	}
	
	void CloseWindowEvent::init(InteractionInitInfo interactionInitInfo) {
		KeyEvent_Simple::init(interactionInitInfo);
		window = &interactionInitInfo.window;
	}
	
	KeyEvent* CloseWindowEvent::copy() {
		auto closeWindow{new CloseWindowEvent{}};
		copy(closeWindow);
		return closeWindow;
	}
	
	bool DecodePointer<CloseWindowEvent>::decodePointer(const YAML::Node& node, CloseWindowEvent*& closeWindowEvent) {
		closeWindowEvent = new CloseWindowEvent {};
		return true;
	}
}