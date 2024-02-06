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
		
		orl::Option<std::vector<BaseCharacter*>::iterator> get_start();
		
		orl::Option<std::vector<BaseCharacter*>::iterator> get_end();
		
		void update(sf::Vector2i mouse_position, bool press) override;
		
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		Text* text;
		orl::Option<std::vector<BaseCharacter*>::iterator> start, end;
	};
}

template<>
struct ieml::Decode<char, ie::TextSelectionAction::Make> {
	static orl::Option<ie::TextSelectionAction::Make> decode(ieml::Node const& node);
};