#include <gtest/gtest.h>
#include "IE/component/IComponent/IScalable/BasicInteractiveData/BaseButton/ButtonPanel/ButtonPanel.hpp"
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

/*
TEST(IComponent, ButtonPanel) {
	InitInfoData data{{100, 100}};
	
	ie::ButtonPanel button_panel{
		{
			ie::make_box_ptr<ie::Panel::Make>(
				ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Red),
				ie::make_box_ptr<ie::PointingHidePanelInteraction::Make>(),
				ie::make_box_ptr<ie::Sizing2::Make>(sf::Vector2f{10, 10}),
				ie::make_box_ptr<ie::Positioning2::Make>(sf::Vector2f{0.5f, 0.5f})
			),
			ie::make_box_ptr<ie::PointingDisplayPanelInteraction::Make>(),
			ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Green),
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(data.update_manager.size(), 1);
	ASSERT_EQ(&data.update_manager.get(0), &button_panel);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 1);
	ASSERT_EQ(&data.panel_manager.get(0), &button_panel.get_panel());
	
	ASSERT_EQ(button_panel.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(button_panel.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(button_panel.get_size(), sf::Vector2f{});
	ASSERT_EQ(button_panel.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(button_panel.get_position(), sf::Vector2f{});
	ASSERT_EQ(button_panel.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(button_panel.update_interactions({}), true);
	
	button_panel.set_size({5, 11});
	ASSERT_EQ(button_panel.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(button_panel.get_area_size(), (sf::Vector2f{5, 11}));
	
	button_panel.set_position({19, 39});
	ASSERT_EQ(button_panel.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(button_panel.get_area_position(), (sf::Vector2f{19, 39}));
	
	button_panel.resize({7, 13}, {23, 41});
	ASSERT_EQ(button_panel.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(button_panel.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(button_panel.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(button_panel.get_area_position(), (sf::Vector2f{23, 41}));
	
	button_panel.move({10, 5});
	ASSERT_EQ(button_panel.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(button_panel.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/ButtonPanel.png"));
}
*/
