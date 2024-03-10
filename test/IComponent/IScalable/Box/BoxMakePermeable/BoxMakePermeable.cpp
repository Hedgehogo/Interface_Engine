#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxMakePermeable/BoxMakePermeable.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "_image_equal/image_equal.hpp"

TEST(IComponent, BoxMakePermeable) {
	InitInfoData data{{100, 100}};
	
	ie::BoxMakePermeable box_make_permeable{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green)
		},
		data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_make_permeable.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_make_permeable.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_make_permeable.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_make_permeable.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_make_permeable.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_make_permeable.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_make_permeable.update_interactions({}), false);
	
	box_make_permeable.set_size({5, 11});
	ASSERT_EQ(box_make_permeable.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_make_permeable.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_make_permeable.set_position({19, 39});
	ASSERT_EQ(box_make_permeable.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_make_permeable.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_make_permeable.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_make_permeable.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_make_permeable.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_make_permeable.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_make_permeable.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_make_permeable.move({10, 5});
	ASSERT_EQ(box_make_permeable.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_make_permeable.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxMakePermeable.png"));
}