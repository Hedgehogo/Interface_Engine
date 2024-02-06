#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxConstBezel/BoxConstBezel.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

TEST(IComponent, BoxConstBezel) {
	InitInfoData data{{100, 100}};
	
	ie::BoxConstBezel box_const_bezel{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::INonInteractive::Make, ie::FullColor::Make>(sf::Color::Red),
			1
		},
		data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 2);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_const_bezel.get_min_size(), (sf::Vector2f{2, 2}));
	ASSERT_EQ(box_const_bezel.get_normal_size(), (sf::Vector2f{2, 2}));
	ASSERT_EQ(box_const_bezel.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_const_bezel.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_const_bezel.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_const_bezel.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_const_bezel.update_interactions({}), true);
	
	box_const_bezel.set_size({5, 11});
	ASSERT_EQ(box_const_bezel.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_const_bezel.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_const_bezel.set_position({19, 39});
	ASSERT_EQ(box_const_bezel.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_const_bezel.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_const_bezel.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_const_bezel.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_const_bezel.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_const_bezel.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_const_bezel.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_const_bezel.move({10, 5});
	ASSERT_EQ(box_const_bezel.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_const_bezel.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxConstBezel.png"));
}