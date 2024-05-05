#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/BaseTextBlock/InteractiveTextBlock/InteractiveTextBlock.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

TEST(IComponent_Text, InteractiveTextBlock) {
	sf::Font font{};
	font.loadFromFile("../../example-resources/segoeui.ttf");
	
	InitInfoData data{{100, 100}};
	InitInfoData text_data{{100, 100}};
	
	ie::InteractiveTextBlock interactive_text_block{
		{
			ie::make_box_ptr<ie::EmptyInteraction::Make>(),
			"aaa bbb"
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
	
	ASSERT_FALSE(interactive_text_block.in({50, 50}));
	ASSERT_TRUE(interactive_text_block.in({1, -1}));
	ASSERT_TRUE(interactive_text_block.handle_event(ie::Event::Pointer({std::numeric_limits<size_t>::max(), {}})));
}