#pragma once

#include "IE/IComponent/IUnscalable/Text/TextInteraction/TextAction/TextAction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class BaseCharacter;
	
	class TextSelectionAction : public BasicBaseKeyAction<Text&> {
	public:
		TextSelectionAction();
		
		void init(TextInteractionInitInfo initInfo) override;
		
		std::vector<BaseCharacter*>::iterator getStart();
		
		std::vector<BaseCharacter*>::iterator getEnd();
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		TextSelectionAction* copy() override;
	
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
	struct DecodePointer<TextSelectionAction> {
		static bool decodePointer(const YAML::Node&, TextSelectionAction*& textSelectionAction);
	};
}