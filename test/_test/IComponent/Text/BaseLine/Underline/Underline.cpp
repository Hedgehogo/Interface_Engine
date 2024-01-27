#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/BaseLine/Underline/Underline.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent_Text, Underline) {
	sf::Font font{};
	font.loadFromFile("../../example-resources/msyh.ttc");
	{
		InitInfoData data{{100, 100}};
		ie::Underline strike_through{
			ie::Underline::Make{},
			{
				14,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/Underline-null-14-Red-20-60-60.png"));
	}
	{
		InitInfoData data{{100, 100}};
		ie::Underline strike_through{
			ie::Underline::Make{},
			{
				14,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.move({10, 10});
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/Underline-null-14-Red-30-70-70.png"));
	}
	{
		InitInfoData data{{100, 100}};
		ie::Underline strike_through{
			ie::Underline::Make{sf::Color::Blue},
			{
				14,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/UnderlineUnderline-Blue-14-Red-20-60-60.png"));
	}
	{
		InitInfoData data{{100, 100}};
		ie::Underline strike_through{
			ie::Underline::Make{},
			{
				40,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/UnderlineUnderline-null-40-Red-20-60-60.png"));
	}
}