#include "textInteraction.hpp"

namespace ui {
	TextInteraction::TextInteraction() : text(nullptr) {
	}
	
	void TextInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		this->text = &textInteractionInitInfo.text;
	}
	
	Text* TextInteraction::getText() {
		return text;
	}
	
	void TextInteraction::setText(Text* text) {
		this->text = text;
	}
}