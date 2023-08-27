#pragma once

#include "IE/IComponent/IUnscalable/Text/TextInteraction/TextAction/TextAction.hpp"
#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class TextCopyAction : public BasicBaseKeyAction<Text&> {
	public:
		TextCopyAction();
		
		void init(TextInteractionInitInfo initInfo) override;
		
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