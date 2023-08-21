#include "TextAddBlockInteractionEvent.hpp"

namespace ui {
	TextAddBlockInteractionEvent::TextAddBlockInteractionEvent(TextInteraction& interaction) : AddBlockInteractionEvent(interaction) {
	}
	
	void TextAddBlockInteractionEvent::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextEvent::init(textInteractionInitInfo);
		AddBlockInteractionEvent::init(textInteractionInitInfo.toGeneral());
	}
	
	void TextAddBlockInteractionEvent::setText(ui::Text* text) {
		TextEvent::setText(text);
		dynamic_cast<TextInteraction*>(interaction)->setText(text);
	}
	
	TextAddBlockInteractionEvent* TextAddBlockInteractionEvent::copy() {
		return new TextAddBlockInteractionEvent{*this};
	}
	
	bool DecodePointer<TextAddBlockInteractionEvent>::decodePointer(const YAML::Node& node, TextAddBlockInteractionEvent*& textAddBlockInteractionEvent) {
		textAddBlockInteractionEvent = new TextAddBlockInteractionEvent{*node["interaction"].as<TextInteraction*>()};
		return true;
	}
}