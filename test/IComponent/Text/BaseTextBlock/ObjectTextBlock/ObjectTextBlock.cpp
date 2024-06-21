#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/BaseTextBlock/ObjectTextBlock/ObjectTextBlock.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Empty/Empty.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent_Text, ObjectTextBlock) {
	sf::Font font{};
	font.loadFromFile("../../example-resources/msyh.ttc");
	{
		InitInfoData data{{100, 100}};
		InitInfoData text_data{{100, 100}};
		
		ie::ObjectTextBlock object_text_block{
			{
				ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Red),
				30.f
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
		
		ASSERT_TRUE(object_text_block.handle_event(ie::Event::Pointer({})));
		
		auto characters{object_text_block.get_characters()};
		
		ASSERT_EQ(characters.size(), 1);
		ASSERT_EQ(characters[0]->is_special(), ie::BaseCharacter::Special::FullLine);
	}
	{
		InitInfoData data{{100, 100}};
		InitInfoData text_data{{100, 100}};
		
		ie::ObjectTextBlock object_text_block{
			ie::ObjectTextBlock::Make{
                    ie::make_box_ptr<ie::Empty::Make>(),
				sf::Vector2f{10, 10},
				true
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
		
		ASSERT_FALSE(object_text_block.handle_event(ie::Event::Pointer({})));
		
		auto characters{object_text_block.get_characters()};
		
		ASSERT_EQ(characters.size(), 1);
		ASSERT_EQ(characters[0]->is_special(), ie::BaseCharacter::Special::No);
	}
	{
		InitInfoData data{{100, 100}};
		InitInfoData text_data{{100, 100}};
		
		ie::ObjectTextBlock object_text_block{
			ie::ObjectTextBlock::Make{
                    ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Red),
				sf::Vector2f{10, 10},
				false
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
		
		auto characters{object_text_block.get_characters()};
		
		ASSERT_EQ(characters.size(), 1);
		ASSERT_EQ(characters[0]->is_special(), ie::BaseCharacter::Special::Object);
	}
}