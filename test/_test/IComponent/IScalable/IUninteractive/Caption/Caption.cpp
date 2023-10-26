#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/Caption/Caption.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <fstream>

TEST(IComponent, Caption) {
	InitInfoData data{{100, 100}};
	
	std::basic_ifstream<char32_t> file{"test-src/Caption.txt"};
	std::u32string str;
	std::getline(file, str, U'\0');
	
	sf::Font font{};
	font.loadFromFile("../../example-resources/msyh.ttc");
	ie::Caption caption{
		{
			sf::String{ie::u32_string_to_uint32_string(str)},
			ie::make_box_ptr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Green),
			font
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &caption);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&caption.get_render_target(), &data.render_target);
	ASSERT_EQ(caption.get_min_size(), (sf::Vector2f{6, 10}));
	ASSERT_EQ(caption.get_normal_size(), (sf::Vector2f{51, 11}));
	ASSERT_EQ(caption.get_size(), sf::Vector2f{});
	ASSERT_EQ(caption.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(caption.get_position(), sf::Vector2f{});
	ASSERT_EQ(caption.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(caption.update_interactions({}), true);
	
	caption.set_size({6, 11});
	ASSERT_EQ(caption.get_size(), (sf::Vector2f{6, 11}));
	ASSERT_EQ(caption.get_area_size(), (sf::Vector2f{6, 11}));
	
	caption.set_position({19, 39});
	ASSERT_EQ(caption.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(caption.get_area_position(), (sf::Vector2f{19, 39}));
	
	caption.resize({93, 13}, {5, 41});
	ASSERT_EQ(caption.get_size(), (sf::Vector2f{93, 13}));
	ASSERT_EQ(caption.get_area_size(), (sf::Vector2f{93, 13}));
	ASSERT_EQ(caption.get_position(), (sf::Vector2f{5, 41}));
	ASSERT_EQ(caption.get_area_position(), (sf::Vector2f{5, 41}));
	
	caption.move({2, 5});
	ASSERT_EQ(caption.get_position(), (sf::Vector2f{7, 46}));
	ASSERT_EQ(caption.get_area_position(), (sf::Vector2f{7, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Caption.png", 0.001));
}