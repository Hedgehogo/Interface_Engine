#pragma once

#include "../textEvent.hpp"
#include "../../../../../../interaction/event/key/addInteraction/blockInteraction/addBlockInteractionEvent.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../../interaction/textInteraction.hpp"

namespace ui {
	class TextAddBlockInteractionEvent : public TextEvent, public AddBlockInteractionEvent{
	public:
		explicit TextAddBlockInteractionEvent(TextInteraction &interaction);

		void init(ui::Text *text, InteractionManager& interactionManager);

		void setText(ui::Text *text) override;

		TextAddBlockInteractionEvent *copy() override;
	};

	bool convertPointer(const YAML::Node &node, TextAddBlockInteractionEvent *&textAddBlockInteractionEvent);
	
	template<>
	struct DecodePointer<TextAddBlockInteractionEvent> {
		static bool decodePointer(const YAML::Node &node, TextAddBlockInteractionEvent *&textAddBlockInteractionEvent);
	};
}