#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextEvent/TextEvent.hpp"
#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class BaseCharacter;
	
	class TextSelectionEvent : public BasicBaseKeyEvent<Text&> {
	public:
		TextSelectionEvent();
		
		void init(TextInteractionInitInfo initInfo) override;
		
		std::vector<BaseCharacter*>::iterator getStart();
		
		std::vector<BaseCharacter*>::iterator getEnd();
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		TextSelectionEvent* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		Text* text;
		std::vector<BaseCharacter*>::iterator start;
		std::vector<BaseCharacter*>::iterator end;
	};
	
	template<>
	struct DecodePointer<TextSelectionEvent> {
		static bool decodePointer(const YAML::Node&, TextSelectionEvent*& textSelectionEvent);
	};
}