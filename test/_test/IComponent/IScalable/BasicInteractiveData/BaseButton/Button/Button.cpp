#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/BasicInteractiveData/BaseButton/Button/Button.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

TEST(IComponent, Button) {
	InitInfoData data{{100, 100}};
	
	ie::Button button{
		{
			ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::EmptyInteraction::Make>(),
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(data.update_manager.size(), 1);
	ASSERT_EQ(&data.update_manager.get(0), &button);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(button.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(button.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(button.get_size(), sf::Vector2f{});
	ASSERT_EQ(button.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(button.get_position(), sf::Vector2f{});
	ASSERT_EQ(button.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(button.update_interactions({}), true);
	
	button.set_size({5, 11});
	ASSERT_EQ(button.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(button.get_area_size(), (sf::Vector2f{5, 11}));
	
	button.set_position({19, 39});
	ASSERT_EQ(button.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(button.get_area_position(), (sf::Vector2f{19, 39}));
	
	button.resize({7, 13}, {23, 41});
	ASSERT_EQ(button.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(button.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(button.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(button.get_area_position(), (sf::Vector2f{23, 41}));
	
	button.move({10, 5});
	ASSERT_EQ(button.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(button.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Button.png"));
}