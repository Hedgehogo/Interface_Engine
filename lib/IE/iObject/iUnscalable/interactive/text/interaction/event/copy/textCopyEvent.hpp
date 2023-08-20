#pragma once

#include "IE/iObject/iUnscalable/interactive/text/interaction/event/textEvent.hpp"
#include "IE/interaction/event/key/simple/keyEventSimple.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class TextCopyEvent : public KeyEvent_Simple, public TextEvent {
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