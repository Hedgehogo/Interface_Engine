#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Interface/Interface.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "image_equal/image_equal.hpp"

TEST(IComponent, Interface) {
	InitInfoData data{{100, 100}};
	
	ie::Interface interface{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green)
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &interface);
	ASSERT_EQ(data.update_manager.size(), 1);
	ASSERT_EQ(&data.update_manager.get(0), &interface);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(interface.get_draw_manager().size(), 1);
	ASSERT_EQ(interface.get_update_manager().size(), 0);
	ASSERT_EQ(interface.get_interaction_manager().size(), 0);
	ASSERT_EQ(interface.get_panel_manager().size(), 0);
	
	ASSERT_EQ(&interface.get_render_target(), &data.render_target);
	ASSERT_EQ(interface.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(interface.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(interface.get_size(), sf::Vector2f{});
	ASSERT_EQ(interface.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(interface.get_position(), sf::Vector2f{});
	ASSERT_EQ(interface.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(interface.update_interactions({}), true);
	
	interface.set_size({5, 11});
	ASSERT_EQ(interface.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(interface.get_area_size(), (sf::Vector2f{5, 11}));
	
	interface.set_position({19, 39});
	ASSERT_EQ(interface.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(interface.get_area_position(), (sf::Vector2f{19, 39}));
	
	interface.resize({7, 13}, {23, 41});
	ASSERT_EQ(interface.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(interface.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(interface.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(interface.get_area_position(), (sf::Vector2f{23, 41}));
	
	interface.move({10, 5});
	ASSERT_EQ(interface.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(interface.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Interface.png"));
}