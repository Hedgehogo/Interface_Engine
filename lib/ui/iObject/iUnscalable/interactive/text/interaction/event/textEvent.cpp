#include "textEvent.hpp"

namespace ui {
	Text* TextEvent::getText() const {
		return text;
	}
	
	void TextEvent::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextEvent::text = text;
	}
	
	void TextEvent::setText(Text* text) {
		TextEvent::text = text;
	}
}