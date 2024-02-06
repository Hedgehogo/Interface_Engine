#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/BaseCharacter/ObjectCharacter/ObjectCharacter.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/component/IComponent/IScalable/Box/BoxAlternative/BoxAlternative.hpp>

TEST(IComponent_Text, ObjectCharacter) {
	{
		InitInfoData data{{100, 100}};
		
		auto object{
                ie::make_box_ptr<ie::BoxAlternative>(
				ie::BoxAlternative::Make{
                        ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Red),
                        ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Blue),
					{10, 10}
				},
				data.make_init_info()
			)
		};
		sf::Vector2f full_color_min_size{object->get_min_size()};
		
		ie::ObjectCharacter character{
			std::move(object),
		};
		
		ASSERT_FALSE(character.get_rerender());
		character.set_rerender(true);
		ASSERT_TRUE(character.get_rerender());
		character.set_rerender(false);
		
		ASSERT_EQ(character.get_char(), U'\0');
		ASSERT_EQ(character.get_size_texture(), sf::Vector2i(full_color_min_size));
		ASSERT_EQ(character.get_kerning(U'd'), 0);
		ASSERT_EQ(character.get_height(), full_color_min_size.y);
		ASSERT_EQ(character.get_advance(), full_color_min_size.x);
		ASSERT_EQ(character.is_enter(), false);
		ASSERT_EQ(character.is_special(), ie::BaseCharacter::Special::No);
		ASSERT_LE(character.get_min_advance(), full_color_min_size.x);
		ASSERT_TRUE(character.update_interactions({}));
	}
	{
		InitInfoData data{{100, 100}};

        ie::BoxPtr<ie::FullColor> full_color{
			new ie::FullColor{
				{
					sf::Color::Red
				},
				data.make_init_info()
			}
		};
		
		full_color->set_size({10, 20});
		
		ie::ObjectCharacter character{
			std::move(full_color),
		};
		
		ASSERT_EQ(character.get_size_texture(), (sf::Vector2i{10, 20}));
		ASSERT_EQ(character.get_height(), 20);
		ASSERT_EQ(character.get_advance(), 10);
		ASSERT_LE(character.get_min_advance(), 10);
		
		character.set_position({40, 40});
		data.draw_manager.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/ObjectCharacter-40-40-false.png"));
		character.set_rerender(false);
		
		data.render_target.clear(sf::Color::Transparent);
		character.move({10, 10});
		data.draw_manager.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/ObjectCharacter-50-50-false.png"));
		character.set_rerender(false);
	}
	{
		InitInfoData data{{100, 100}};

        ie::BoxPtr<ie::FullColor> full_color{
			new ie::FullColor{
				{
					sf::Color::Red
				},
				data.make_init_info()
			}
		};
		
		full_color->set_size({10, 20});
		
		ie::ObjectCharacter character{
			std::move(full_color),
			ie::ObjectCharacter::ObjectSpecial::FullLine
		};
		
		ASSERT_EQ(character.is_special(), ie::BaseCharacter::Special::FullLine);
		
		character.resize({40, 40}, 100);
		data.draw_manager.draw();
		
		ASSERT_TRUE(character.get_rerender());
		ASSERT_TRUE(data.render_equal_with_save("test-src/ObjectCharacter-40-40-true.png"));
	}
	{
		InitInfoData data{{100, 100}};

        ie::BoxPtr<ie::FullColor> full_color{
			new ie::FullColor{
				{
					sf::Color::Red
				},
				data.make_init_info()
			}
		};
		
		full_color->set_size({10, 20});
		
		ie::ObjectCharacter character{
			std::move(full_color),
			ie::ObjectCharacter::ObjectSpecial::Object
		};
		
		ASSERT_EQ(character.is_special(), ie::BaseCharacter::Special::Object);
	}
}