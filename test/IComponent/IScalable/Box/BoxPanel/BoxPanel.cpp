#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxPanel/BoxPanel.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "_image_equal/image_equal.hpp"

TEST(IComponent, BoxPanel) {
	InitInfoData data{{100, 100}};
	
	ie::BoxPanel box_panel{
		{
			ie::make_box_ptr<ie::ConstPanel::Make>(
				ie::make_box_ptr<ie::FullColor::Make>(sf::Color::Red),
				ie::make_box_ptr<ie::Sizing2::Make>(sf::Vector2f{10, 10}),
				ie::make_box_ptr<ie::Positioning2::Make>(sf::Vector2f{0.5f, 0.5f})
			),
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 1);
	ASSERT_EQ(&data.panel_manager.get(0), &box_panel.get_panel());
	
	ASSERT_EQ(box_panel.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_panel.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_panel.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_panel.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_panel.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_panel.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_panel.update_interactions(ie::Event::Touch(std::numeric_limits<size_t>::max(), {})), true);
	
	box_panel.set_size({5, 11});
	ASSERT_EQ(box_panel.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_panel.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_panel.set_position({19, 39});
	ASSERT_EQ(box_panel.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_panel.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_panel.resize({8, 14}, {23, 41});
	ASSERT_EQ(box_panel.get_size(), (sf::Vector2f{8, 14}));
	ASSERT_EQ(box_panel.get_area_size(), (sf::Vector2f{8, 14}));
	ASSERT_EQ(box_panel.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_panel.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_panel.move({10, 5});
	ASSERT_EQ(box_panel.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_panel.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	data.panel_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxPanel.png"));
}