#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/BasicInteractiveData/MovableBorder/MovableBorder.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include <_image_equal/image_equal.hpp>

TEST(IComponent, MovableBorder) {
	InitInfoData data{{100, 100}};
	
	ie::SMRFloat value{0.f};
	ie::MovableBorder box_movable_border{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
			false,
			value
		},
		data.make_init_info()
	};
	data.update_manager.update();
	
	ASSERT_EQ(data.draw_manager.size(), 2);
	ASSERT_EQ(data.update_manager.size(), 1);
	ASSERT_EQ(&data.update_manager.get(0), &box_movable_border);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_movable_border.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_movable_border.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_movable_border.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_movable_border.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_movable_border.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_movable_border.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_movable_border.handle_event(ie::Event::Pointer({})), true);
	
	box_movable_border.set_size({5, 11});
	ASSERT_EQ(box_movable_border.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_movable_border.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_movable_border.set_position({19, 39});
	ASSERT_EQ(box_movable_border.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_movable_border.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_movable_border.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_movable_border.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_movable_border.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_movable_border.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_movable_border.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_movable_border.move({10, 5});
	ASSERT_EQ(box_movable_border.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_movable_border.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/MovableBorder-0.0.png"));
	
	value.set(0.7f);
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/MovableBorder-0.7.png"));
}