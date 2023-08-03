#pragma once

#include "ui/iObject/iUnscalable/interactive/text/interaction/event/textEvent.hpp"
#include "ui/interaction/event/key/simple/keyEventSimple.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class TextCopyEvent : public KeyEvent_Simple, public TextEvent {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		TextCopyEvent* copy() override;
		
		~TextCopyEvent() = default;
	};
	
	template<>
	struct DecodePointer<TextCopyEvent> {
		static bool decodePointer(const YAML::Node&, TextCopyEvent*& textCopyEvent);
	};
}