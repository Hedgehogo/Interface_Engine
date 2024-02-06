#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/BaseTextBlock/TextBlock/TextBlock.hpp>
#include <IE/component/IComponent/Text/BaseLine/Underline/Underline.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>


TEST(IComponent_Text, TextBlock) {
	sf::Font font{};
	font.loadFromFile("../../example-resources/segoeui.ttf");
	{
		InitInfoData data{{100, 100}};
		InitInfoData text_data{{100, 100}};
		
		ie::TextBlock text_block{
			{
				"aaa bbb",
				{},
				{},
				{},
				ie::make_vector(
                    ie::make_box_ptr<ie::BaseLine::Make, ie::Underline::Make>()
				)
			},
			{
				data.make_init_info(),
				text_data.render_target,
				text_data.draw_manager,
				text_data.interaction_manager,
				{
					sf::Color::Black,
					sf::Color::White,
					sf::Color::Blue,
					sf::Color::Black,
					{150, 150, 150},
					font,
					sf::Text::Style::StrikeThrough,
					30
				}
			}
		};
		
		auto characters{text_block.get_characters()};
		auto character0{characters[0]};
		float advance_without_kerning{characters[0]->get_advance()};
		text_block.set_kerning('+');
		
		ASSERT_EQ(characters.size(), 7);
		ASSERT_EQ(characters[0]->get_char(), U'a');
		ASSERT_EQ(characters[1]->get_char(), U'a');
		ASSERT_EQ(characters[2]->get_char(), U'a');
		ASSERT_EQ(characters[3]->get_char(), U' ');
		ASSERT_EQ(characters[4]->get_char(), U'b');
		ASSERT_EQ(characters[5]->get_char(), U'b');
		ASSERT_EQ(characters[6]->get_char(), U'b');
		
		ASSERT_NE(character0->get_advance(), advance_without_kerning);
		ASSERT_FALSE(text_block.in({50, 50}));
		ASSERT_FALSE(text_block.in({1, -1}));
		ASSERT_FALSE(text_block.update_interactions({0, 0}));
		
		ASSERT_EQ(character0->get_line().size(), 2);
		ASSERT_EQ(&character0->get_line(), &characters[1]->get_line());
		
		character0->resize({50, 50}, 0);
		character0->draw();
		ASSERT_TRUE(text_data.render_equal_with_save("test-src/TextBlock-1.png"));
		text_data.render_target.clear(sf::Color::Transparent);
		
		character0->set_selection(true);
		character0->draw();
		ASSERT_TRUE(text_data.render_equal_with_save("test-src/TextBlock-2.png"));
		text_data.render_target.clear(sf::Color::Transparent);
		
		character0->set_active(false);
		character0->draw();
		ASSERT_TRUE(text_data.render_equal_with_save("test-src/TextBlock-3.png"));
	}
	{
		InitInfoData data{{100, 100}};
		InitInfoData text_data{{100, 100}};
		
		ie::TextBlock text_block{
			{
				"aaa bbb",
				sf::Color::Red,
				font,
				{},
				std::vector<ie::BoxPtr<ie::BaseLine::Make>>{},
				30,
				sf::Color::Yellow,
				sf::Color::Green,
				sf::Color::Magenta,
				sf::Color::Cyan
			},
			{
				data.make_init_info(),
				text_data.render_target,
				text_data.draw_manager,
				text_data.interaction_manager,
				{
					sf::Color::Black,
					sf::Color::White,
					sf::Color::Blue,
					sf::Color::Black,
					{150, 150, 150},
					font,
					{},
					30
				}
			}
		};
		auto characters{text_block.get_characters()};
		auto character0{characters[0]};
		
		ASSERT_EQ(character0->get_line().size(), 0);
		ASSERT_EQ(&character0->get_line(), &characters[1]->get_line());
		
		character0->resize({50, 50}, 0);
		character0->draw();
		ASSERT_TRUE(text_data.render_equal_with_save("test-src/TextBlock-4.png"));
		text_data.render_target.clear(sf::Color::Transparent);
		
		character0->set_selection(true);
		character0->draw();
		ASSERT_TRUE(text_data.render_equal_with_save("test-src/TextBlock-5.png"));
		text_data.render_target.clear(sf::Color::Transparent);
		
		character0->set_active(false);
		character0->draw();
		ASSERT_TRUE(text_data.render_equal_with_save("test-src/TextBlock-6.png"));
	}
}