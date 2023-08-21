#include "CloseWindowEvent.hpp"

#include "IE/Window/Window.hpp"

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
		BaseKeyEvent::init(interactionInitInfo);
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