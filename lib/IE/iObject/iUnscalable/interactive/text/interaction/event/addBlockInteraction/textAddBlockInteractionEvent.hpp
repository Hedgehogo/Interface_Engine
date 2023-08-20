#pragma once

#include "IE/iObject/iUnscalable/interactive/text/Interaction/event/textEvent.hpp"
#include "IE/Interaction/IEvent/KeyEvent/AddInteractionEvent/AddBlockInteractionEvent/AddBlockInteractionEvent.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "IE/iObject/iUnscalable/interactive/text/Interaction/Interaction/textInteraction.hpp"

namespace ui {
	class TextAddBlockInteractionEvent : public TextEvent, public AddBlockInteractionEvent {
	public:
		explicit TextAddBlockInteractionEvent(TextInteraction& interaction);
		
		void init(TextInteractionInitInfo textInteractionInitInfo) override;
		
		void setText(ui::Text* text) override;
		
		TextAddBlockInteractionEvent* copy() override;
	};
	
	template<>
	struct DecodePointer<TextAddBlockInteractionEvent> {
		static bool decodePointer(const YAML::Node& node, TextAddBlockInteractionEvent*& textAddBlockInteractionEvent);
	};
}