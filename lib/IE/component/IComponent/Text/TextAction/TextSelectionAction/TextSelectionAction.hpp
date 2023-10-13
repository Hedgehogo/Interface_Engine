#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class BaseCharacter;
	class Text;
	
	class TextSelectionAction : public BasicBaseKeyAction<Text&> {
	public:
		struct Make : BasicBaseKeyAction<Text&>::Make {
			TextSelectionAction* make(BasicActionInitInfo<Text&> initInfo) override;
		};
		
		TextSelectionAction(Make&& make, BasicActionInitInfo<Text&> initInfo);
		
		TextSelectionAction();
		
		void init(BasicActionInitInfo<Text&> initInfo) override;
		
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