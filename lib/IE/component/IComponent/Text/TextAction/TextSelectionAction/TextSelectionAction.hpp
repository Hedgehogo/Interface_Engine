#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class BaseCharacter;
	class Text;
	
	class TextSelectionAction : public BasicBaseKeyAction<Text&> {
	public:
		struct Make : BasicBaseKeyAction<Text&>::Make {
			TextSelectionAction* make(BasicActionInitInfo<Text&> init_info) override;
		};
		
		TextSelectionAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
		TextSelectionAction();
		
		void init(BasicActionInitInfo<Text&> init_info) override;
		
		orl::Option<std::vector<BaseCharacter*>::iterator> get_start();
		
		orl::Option<std::vector<BaseCharacter*>::iterator> get_end();
		
		void update(sf::Vector2i mouse_position, bool press) override;
		
		TextSelectionAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		Text* text;
		orl::Option<std::vector<BaseCharacter*>::iterator> start, end;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<TextSelectionAction> {
		static bool decode_pointer(const YAML::Node&, TextSelectionAction*& text_selection_action);
	};
	*/
}