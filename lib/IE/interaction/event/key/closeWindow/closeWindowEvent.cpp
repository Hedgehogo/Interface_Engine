#include "closeWindowEvent.hpp"

#include "IE/window/window.hpp"

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
	
	void CloseWindowEvent::init(InteractionInitInfo interactionInitInfo) {
		KeyEvent_Simple::init(interactionInitInfo);
		window = &interactionInitInfo.window;
	}
	
	KeyEvent* CloseWindowEvent::copy() {
		return new CloseWindowEvent{*this};
	}
	
	bool DecodePointer<CloseWindowEvent>::decodePointer(const YAML::Node&, CloseWindowEvent*& closeWindowEvent) {
		closeWindowEvent = new CloseWindowEvent{};
		return true;
	}
}