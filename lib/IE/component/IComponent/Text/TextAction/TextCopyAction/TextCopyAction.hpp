#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class Text;
	
	class TextCopyAction : public BasicBaseKeyAction<Text&> {
	public:
		struct Make : public BasicBaseKeyAction<Text&>::Make {
			TextCopyAction* make(BasicActionInitInfo<Text&> init_info);
		};
		
		TextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
		TextCopyAction();
		
		void init(BasicActionInitInfo<Text&> init_info) override;
		
		TextCopyAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		Text* text;
	};
	
	template<>
	struct DecodePointer<TextCopyAction> {
		static bool decode_pointer(const YAML::Node&, TextCopyAction*& text_copy_action);
	};
}