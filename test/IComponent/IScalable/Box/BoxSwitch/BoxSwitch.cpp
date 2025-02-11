#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxSwitch/BoxSwitch.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/shared/ISReadable/SReadable/SReadable.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "_image_equal/image_equal.hpp"

TEST(IComponent, BoxSwitch) {
	InitInfoData data{{100, 100}};
	
	ie::SMBool value{false};
	ie::BoxSwitch box_switch{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
			value
		}, data.make_init_info()
	};
	data.update_manager.update();
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &box_switch);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.trigger_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_switch.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_switch.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_switch.handle_event(ie::Event::Pointer({})), true);
	
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
	
	value.set(true);
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxSwitch-true.png"));
}