#include "textEvent.hpp"

namespace ui {
	Text* TextEvent::getText() const {
		return text;
	}
	
	void TextEvent::init(Text* text) {
		TextEvent::text = text;
	}
	
	void TextEvent::setText(Text* text) {
		TextEvent::text = text;
	}
}