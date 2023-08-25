#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextEvent/TextEvent.hpp"
#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class TextCopyEvent : public BasicBaseKeyEvent<Text&> {
	public:
		TextCopyEvent();
		
		void init(TextInteractionInitInfo initInfo) override;
		
		TextCopyEvent* copy() override;
		
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		Text* text;
	};
	
	template<>
	struct DecodePointer<TextCopyEvent> {
		static bool decodePointer(const YAML::Node&, TextCopyEvent*& textCopyEvent);
	};
}