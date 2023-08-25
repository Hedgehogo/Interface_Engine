#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextEvent/TextEvent.hpp"
#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class TextCopyEvent : public BaseKeyEvent, public TextEvent {
	public:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		TextCopyEvent* copy() override;
	};
	
	template<>
	struct DecodePointer<TextCopyEvent> {
		static bool decodePointer(const YAML::Node&, TextCopyEvent*& textCopyEvent);
	};
}