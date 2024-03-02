#include <gtest/gtest.h>
#include <IE/component/IComponent/Text/BaseLine/StrikeThrough/StrikeThrough.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent_Text, StrikeThrough) {
	sf::Font font{};
	font.loadFromFile("../../example-resources/msyh.ttc");
	{
		InitInfoData data{{100, 100}};
		ie::StrikeThrough strike_through{
			ie::StrikeThrough::Make{},
			{
				14,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/StrikeThrough-null-0,3-14-Red-20-60-60.png"));
	}
	{
		InitInfoData data{{100, 100}};
		ie::StrikeThrough strike_through{
			ie::StrikeThrough::Make{},
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
		ASSERT_TRUE(data.render_equal_with_save("test-src/StrikeThrough-null-0,3-14-Red-30-70-70.png"));
	}
	{
		InitInfoData data{{100, 100}};
		ie::StrikeThrough strike_through{
			ie::StrikeThrough::Make{sf::Color::Blue},
			{
				14,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/StrikeThrough-Blue-0,3-14-Red-20-60-60.png"));
	}
	{
		InitInfoData data{{100, 100}};
		ie::StrikeThrough strike_through{
			ie::StrikeThrough::Make{{}, 0.9},
			{
				14,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/StrikeThrough-null-0,9-14-Red-20-60-60.png"));
	}
	{
		InitInfoData data{{100, 100}};
		ie::StrikeThrough strike_through{
			ie::StrikeThrough::Make{},
			{
				40,
				font,
				sf::Color::Red,
				data.render_target
			}
		};
		
		strike_through.resize(20, 60, 60);
		strike_through.draw();
		ASSERT_TRUE(data.render_equal_with_save("test-src/StrikeThrough-null-0,3-40-Red-20-60-60.png"));
	}
}