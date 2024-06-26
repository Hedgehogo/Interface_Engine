#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/TextAction/TextCopyAction/TextCopyAction.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include <IE/component/IComponent/Text/Text.hpp>
#include <IE/component/IComponent/Text/BaseTextBlock/TextBlock/TextBlock.hpp>

template<>
struct ie::ProcessClipboard<std::u32string>{
	static void set_string(std::u32string&, sf::String str){
		ASSERT_EQ(str, "aaa\n");
	}
	
	static sf::String get_string(std::u32string&){
		return {};
	}
};

TEST(IComponent_Text, TextCopyAction) {
	InitInfoData data{{100, 100}};
	sf::Font font{};
	font.loadFromFile("../../example-resources/segoeui.ttf");
	
	ie::Text text{
		ie::Text::Make{
			ie::make_vector(
				ie::make_box_ptr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
					"aaa\naaa"
				)
			),
			font
		},
		data.make_init_info()
	};
	
	std::vector<ie::BaseCharacter*>& text_characters{text.get_characters()};
	
	ie::BasicTextCopyAction<std::u32string> copy_action{
		ie::BasicTextCopyAction<std::u32string>::Make{},
		ie::BasicActionInitInfo<ie::Text&>{
			data.make_init_info(),
			text
		}
	};
	
	text.set_selection({{text_characters.begin()}, {text_characters.begin() + 4}});
	
	copy_action.update(true);
	copy_action.update(false);
}
