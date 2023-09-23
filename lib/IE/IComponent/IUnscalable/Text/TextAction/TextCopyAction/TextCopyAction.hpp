#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class Text;
	
	class TextCopyAction : public BasicBaseKeyAction<Text&> {
	public:
		struct Make : public BasicBaseKeyAction<Text&>::Make {
			TextCopyAction* make(BasicActionInitInfo<Text&> initInfo);
		};
		
		TextCopyAction(Make&& make, BasicActionInitInfo<Text&> initInfo);
		
		TextCopyAction();
		
		void init(BasicActionInitInfo<Text&> initInfo) override;
		
		TextCopyAction* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		Text* text;
	};
	
	template<>
	struct DecodePointer<TextCopyAction> {
		static bool decodePointer(const YAML::Node&, TextCopyAction*& textCopyAction);
	};
}