#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextEvent/TextEvent.hpp"
#include "IE/Interaction/IEvent/BasicKeyEvent/BasicAddInteractionEvent/BasicAddBlockInteractionEvent/BasicAddBlockInteractionEvent.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextInteraction.hpp"

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