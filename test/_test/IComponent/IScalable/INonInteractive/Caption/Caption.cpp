#include <gtest/gtest.h>
#include <IE/utils/utf/to_utf/to_utf.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/Caption/Caption.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <fstream>

TEST(IComponent, BasicCaption) {
	InitInfoData data{{100, 100}};
	
	std::basic_ifstream<char32_t> file1{"test-src/Caption1.txt"};
	std::u32string str1;
	std::getline(file1, str1, U'\0');
	
	std::basic_ifstream<char32_t> file2{"test-src/Caption2.txt"};
	std::u32string str2;
	std::getline(file2, str2, U'\0');
	auto utf32_str2{ie::to_utf32(str2)};
	
	sf::Font font{};
	font.loadFromFile("../../example-resources/msyh.ttc");
	ie::Caption caption{
		ie::Caption::Make{
			ie::to_utf32(str1),
			ie::make_box_ptr<ie::INonInteractive::Make, ie::FullColor::Make>(sf::Color::Green),
			font
		}.set_cut_back(true), data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &caption);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&caption.get_render_target(), &data.render_target);
	ASSERT_EQ(caption.get_min_size(), (sf::Vector2f{6, 13}));
	ASSERT_EQ(caption.get_normal_size(), (sf::Vector2f{50, 13}));
	ASSERT_EQ(caption.get_size(), sf::Vector2f{});
	ASSERT_EQ(caption.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(caption.get_position(), sf::Vector2f{});
	ASSERT_EQ(caption.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(caption.update_interactions({}), true);
	
	caption.set_size({6, 14});
	ASSERT_EQ(caption.get_size(), (sf::Vector2f{6, 14}));
	ASSERT_EQ(caption.get_area_size(), (sf::Vector2f{6, 14}));
	
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
	ASSERT_TRUE(data.render_equal_with_save("test-src/Caption-93.png", 0.001));
	data.render_target.clear(sf::Color::Transparent);
	
	caption.resize({20, 13}, {7, 46});
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Caption-20.png", 0.001));
	data.render_target.clear(sf::Color::Transparent);
	
	auto old_str{caption.text_.getString()};
	caption.set_string(utf32_str2);
	ASSERT_EQ(caption.str_, utf32_str2);
	ASSERT_EQ(caption.text_.getString(), old_str);
	caption.resize({100, 100}, {0, 0});
	ASSERT_EQ(caption.text_.getString(), utf32_str2);
}