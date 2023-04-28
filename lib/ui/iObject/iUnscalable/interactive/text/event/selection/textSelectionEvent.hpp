#pragma once

#include "../../../../../../interaction/event/key/simple/keyEventSimple.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../textEvent.hpp"

namespace ui {
	class BaseCharacter;
	
	class TextSelectionEvent : public KeyEvent_Simple, public TextEvent {
	protected:
		std::vector<BaseCharacter*>::iterator start;
		std::vector<BaseCharacter*>::iterator end;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		TextSelectionEvent();
		
		std::vector<BaseCharacter*>::iterator getStart();
		
		std::vector<BaseCharacter*>::iterator getEnd();
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		TextSelectionEvent* copy();
	};
	
	
	template<>
	struct DecodePointer<TextSelectionEvent> {
		static bool decodePointer(const YAML::Node& node, TextSelectionEvent*& textSelectionEvent);
	};
}