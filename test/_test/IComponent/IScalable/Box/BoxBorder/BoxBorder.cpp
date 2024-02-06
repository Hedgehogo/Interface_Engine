#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxBorder/BoxBorder.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

TEST(IComponent, BoxBorder) {
	InitInfoData data{{100, 100}};
	
	ie::BoxBorder box_border{
		{
			ie::make_vector(
				ie::make_vector(
					ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
					ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
				),
				ie::make_vector(
					ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Blue),
					ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Yellow)
				)
			)
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 4);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_border.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_border.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_border.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_border.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_border.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_border.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_border.update_interactions({}), true);
	
	box_border.set_size({5, 11});
	ASSERT_EQ(box_border.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_border.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_border.set_position({19, 39});
	ASSERT_EQ(box_border.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_border.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_border.resize({8, 14}, {23, 41});
	ASSERT_EQ(box_border.get_size(), (sf::Vector2f{8, 14}));
	ASSERT_EQ(box_border.get_area_size(), (sf::Vector2f{8, 14}));
	ASSERT_EQ(box_border.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_border.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_border.move({10, 5});
	ASSERT_EQ(box_border.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_border.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxBorder.png"));
}