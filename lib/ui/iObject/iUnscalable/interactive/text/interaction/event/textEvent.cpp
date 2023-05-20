#include "textEvent.hpp"

namespace ui {
	Text* TextEvent::getText() const {
		return text;
	}
	
	void TextEvent::copy(TextEvent* textEvent) {
		KeyEvent::copy(textEvent);
		textEvent->text = text;
	}
	
	void TextEvent::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextEvent::text = &textInteractionInitInfo.text;
	}
	
	void TextEvent::setText(Text* text) {
		TextEvent::text = text;
	}
}