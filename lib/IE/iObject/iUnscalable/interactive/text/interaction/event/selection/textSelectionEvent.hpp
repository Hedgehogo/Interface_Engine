#pragma once

#include "IE/Interaction/IEvent/KeyEvent/BaseKeyEvent/BaseKeyEvent.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "IE/iObject/iUnscalable/interactive/text/Interaction/event/textEvent.hpp"

namespace ui {
	class BaseCharacter;
	
	class TextSelectionEvent : public BaseKeyEvent, public TextEvent {
	public:
		TextSelectionEvent();
		
		std::vector<BaseCharacter*>::iterator getStart();
		
		std::vector<BaseCharacter*>::iterator getEnd();
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		TextSelectionEvent* copy() override;
	
	protected:
		std::vector<BaseCharacter*>::iterator start;
		std::vector<BaseCharacter*>::iterator end;
	};
	
	template<>
	struct DecodePointer<TextSelectionEvent> {
		static bool decodePointer(const YAML::Node&, TextSelectionEvent*& textSelectionEvent);
	};
}