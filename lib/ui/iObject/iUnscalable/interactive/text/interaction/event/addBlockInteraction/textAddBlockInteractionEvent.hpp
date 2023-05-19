#pragma once

#include "ui/iObject/iUnscalable/interactive/text/interaction/event/textEvent.hpp"
#include "ui/interaction/event/key/addInteraction/blockInteraction/addBlockInteractionEvent.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "ui/iObject/iUnscalable/interactive/text/interaction/interaction/textInteraction.hpp"

namespace ui {
	class TextAddBlockInteractionEvent : public TextEvent, public AddBlockInteractionEvent {
	public:
		explicit TextAddBlockInteractionEvent(TextInteraction& interaction);
		
		void init(ui::Text* text, InteractionManager& interactionManager);
		
		void setText(ui::Text* text) override;
		
		TextAddBlockInteractionEvent* copy() override;
	};
	
	
	template<>
	struct DecodePointer<TextAddBlockInteractionEvent> {
		static bool decodePointer(const YAML::Node& node, TextAddBlockInteractionEvent*& textAddBlockInteractionEvent);
	};
}