#include <gtest/gtest.h>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <IE/component/IComponent/Text/BaseCharacter/Character/Character.hpp>
#include <IE/component/IComponent/Text/BaseLine/Underline/Underline.hpp>
#include <IE/component/IComponent/Text/BaseLine/StrikeThrough/StrikeThrough.hpp>

TEST(IComponent_Text, Character) {
	
	sf::Font font{};
	font.loadFromFile("../../example-resources/segoeui.ttf");
	
	{
		InitInfoData data{{100, 100}};
		
		auto lines_make{
			ie::make_vector(
            	ie::make_box_ptr<ie::BaseLine::Make, ie::Underline::Make>(sf::Color::Red),
            	ie::make_box_ptr<ie::BaseLine::Make, ie::StrikeThrough::Make>(sf::Color::Blue, 0.6f)
			)
		};
		
		ie::TextVariables text_variables{
			sf::Color::Black,
			sf::Color::White,
			sf::Color::Blue,
			sf::Color::Black,
			sf::Color{150, 150, 150},
			font,
			sf::Text::Style::Regular,
			14
		};
		
		auto lines{
			ie::map_make(
				std::move(lines_make),
				ie::LineInitInfo{
					text_variables.size.except(),
					text_variables.font.except(),
					text_variables.text_color.except(),
					data.render_target
				}
			)
		};
		
		ie::Character character{
			U'a',
			text_variables,
			lines,
			data.render_target
		};
		
		ASSERT_FALSE(character.get_rerender());
		character.set_rerender(true);
		ASSERT_TRUE(character.get_rerender());
		character.set_rerender(false);
		
		ASSERT_EQ(character.get_char(), U'a');
		ASSERT_EQ(character.get_size_texture(), (sf::Vector2i{6, 7}));
		ASSERT_EQ(&character.get_line(), &lines);
		ASSERT_EQ(character.get_kerning(U'd'), 0);
		ASSERT_EQ(character.get_kerning(U'+'), -1);
		ASSERT_EQ(character.get_height(), 14);
		ASSERT_EQ(character.get_advance(), 7);
		ASSERT_EQ(character.is_enter(), false);
		ASSERT_EQ(character.is_special(), ie::BaseCharacter::Special::No);
		ASSERT_LE(character.get_min_advance(), character.get_advance());
		
		character.resize({50, 50}, 0);
		character.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-1.png"));
		character.set_rerender(false);
		
		ASSERT_TRUE(character.in({56, 43}));
		ASSERT_FALSE(character.in({12, 12}));
		
		data.render_target.clear(sf::Color::Transparent);
		character.set_position({40, 40});
		character.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-2.png"));
		character.set_rerender(false);
		
		data.render_target.clear(sf::Color::Transparent);
		character.move({10, 10});
		character.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-3.png"));
		character.set_rerender(false);
		
		data.render_target.clear(sf::Color::Transparent);
		character.set_selection(true);
		character.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-4.png"));
		character.set_rerender(false);
		
		data.render_target.clear(sf::Color::Transparent);
		character.set_active(false);
		character.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-5.png"));
		character.set_rerender(false);
		
		data.render_target.clear(sf::Color::Transparent);
		character.draw();
		character.draw_debug(data.render_target, 0, 0, 0);
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-6.png"));
		
		data.render_target.clear(sf::Color::Transparent);
		ie::Character::set_debug(true);
		character.draw();
		character.draw_debug(data.render_target, 0, 0, 0);
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-7.png"));
	}
	{
		InitInfoData data{{100, 100}};
		
		std::vector<ie::BoxPtr<ie::BaseLine>> lines{};
		
		ie::TextVariables text_variables{
			sf::Color::Black,
			sf::Color::White,
			sf::Color::Blue,
			sf::Color::Black,
			sf::Color{150, 150, 150},
			font,
			sf::Text::Style::Regular,
			14
		};
		
		ie::Character character{
			U' ',
			text_variables,
			lines,
			data.render_target
		};
		
		ASSERT_EQ(character.is_special(), ie::BaseCharacter::Special::Space);
		
		character.resize({50, 50}, 0);
		character.draw();
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-8.png"));
	}
	{
		InitInfoData data{{100, 100}};
		
		std::vector<ie::BoxPtr<ie::BaseLine>> lines{};
		
		ie::TextVariables text_variables{
			sf::Color::Black,
			sf::Color::White,
			sf::Color::Blue,
			sf::Color::Black,
			sf::Color{150, 150, 150},
			font,
			sf::Text::Style::Regular,
			14
		};
		
		ie::Character character{
			U'\n',
			text_variables,
			lines,
			data.render_target
		};
		
		ASSERT_EQ(character.is_special(), ie::BaseCharacter::Special::Enter);
		ASSERT_EQ(character.is_enter(), true);
		
		character.resize({50, 50}, 0);
		character.draw();
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-9.png"));
	}
	{
		InitInfoData data{{100, 100}};
		
		std::vector<ie::BoxPtr<ie::BaseLine>> lines{};
		
		ie::TextVariables text_variables{
			sf::Color::Red,
			sf::Color::Green,
			sf::Color::Yellow,
			sf::Color::Cyan,
			sf::Color::Magenta,
			font,
			sf::Text::Style::Regular,
			14
		};
		
		ie::Character character{
			U'b',
			text_variables,
			lines,
			data.render_target
		};
		
		character.resize({50, 50}, 0);
		character.draw();
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-10.png"));
		
		data.render_target.clear(sf::Color::Transparent);
		character.set_selection(true);
		character.draw();
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-11.png"));
		
		data.render_target.clear(sf::Color::Transparent);
		character.set_active(false);
		character.draw();
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-12.png"));
		
		data.render_target.clear(sf::Color::Transparent);
		character.draw();
		character.draw_debug(data.render_target, 0, 90, 0);
		
		ASSERT_TRUE(data.render_equal_with_save("test-src/Character-13.png"));
	}
}