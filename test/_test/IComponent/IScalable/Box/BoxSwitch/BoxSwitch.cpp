#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxSwitch/BoxSwitch.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

TEST(IComponent, BoxSwitch) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ie::Sbool>(false);
	ie::BoxSwitch box_switch{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
			value
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &box_switch);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_switch.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_switch.update_interactions({}), true);
	
	box_switch.set_size({5, 11});
	ASSERT_EQ(box_switch.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_switch.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_switch.set_position({19, 39});
	ASSERT_EQ(box_switch.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_switch.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_switch.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_switch.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_switch.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_switch.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_switch.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_switch.move({10, 5});
	ASSERT_EQ(box_switch.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_switch.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxSwitch-false.png"));
	
	value->set_value(true);
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxSwitch-true.png"));
}