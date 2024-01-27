#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/TextAction/TextSelectionAction/TextSelectionAction.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <IE/component/IComponent/Text/Text.hpp>
#include <IE/component/IComponent/Text/BaseTextBlock/TextBlock/TextBlock.hpp>

TEST(IComponent_Text, TextSelectionAction) {
	InitInfoData data{{100, 100}};
	sf::Font font{};
	font.loadFromFile("../../example-resources/segoeui.ttf");
	
	ie::Text text{
		ie::Text::Make{
			ie::make_vector(
                    ie::make_box_ptr<ie::BaseTextBlock::Make, ie::TextBlock::Make>(
					U"aaa\naaa"
				)
			),
			&font
		},
		data.make_init_info()
	};
	
	ie::TextSelectionAction selection_action{
		ie::TextSelectionAction::Make{},
		ie::BasicActionInitInfo<ie::Text&>{
			data.make_init_info(),
			text
		}
	};
	
	text.resize({100, 100}, {0,  0});
	
	selection_action.update({2, 5}, true);
	selection_action.update({7, 5}, true);
	
	ASSERT_EQ(text.get_selection_text().length(), 1);
	
	selection_action.update({14, 5}, true);

	ASSERT_EQ(text.get_selection_text().length(), 2);
	
	selection_action.update({14, 30}, true);
	
	ASSERT_EQ(text.get_selection_text().length(), 6);
	
	selection_action.update({14, 30}, false);
	selection_action.update({14, 30}, true);
	selection_action.update({14, 30}, false);
	
	ASSERT_EQ(text.get_selection_text().length(), 0);
	
	selection_action.update({90, 5}, true);
	selection_action.update({90, 30}, true);
	
	ASSERT_EQ(text.get_selection_text().length(), 3);
}