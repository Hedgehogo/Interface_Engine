#include "textAddBlockInteractionEvent.hpp"

namespace ui {
	TextAddBlockInteractionEvent::TextAddBlockInteractionEvent(TextInteraction &interaction) : AddBlockInteractionEvent(interaction) {}

	void TextAddBlockInteractionEvent::init(ui::Text *text, InteractionManager &interactionManager) {
		TextEvent::init(text);
		AddBlockInteractionEvent::init(interactionManager);
	}

	void TextAddBlockInteractionEvent::setText(ui::Text *text) {
		TextEvent::setText(text);
		dynamic_cast<TextInteraction*>(interaction)->setText(text);
	}

	TextAddBlockInteractionEvent *TextAddBlockInteractionEvent::copy() {
		return nullptr;
	}

	bool convertPointer(const YAML::Node &node, TextAddBlockInteractionEvent *& textAddBlockInteractionEvent){
		textAddBlockInteractionEvent = new TextAddBlockInteractionEvent{*node["interaction"].as<TextInteraction*>()};
		return true;
	}
}