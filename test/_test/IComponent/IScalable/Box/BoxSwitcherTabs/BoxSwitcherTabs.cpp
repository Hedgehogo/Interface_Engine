#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxSwitcherTabs/BoxSwitcherTabs.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/shared/ISValue/SRanged/SRanged.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

TEST(IComponent, BoxSwitcherTabs) {
	InitInfoData data{{100, 100}};
	
	ie::SRSize value{0};
	ie::BoxSwitcherTabs box_switcher_tabs{
		{
			ie::make_vector(
				ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
				ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
			),
			value
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 2);
	ASSERT_EQ(data.update_manager.size(), 1);
	ASSERT_EQ(&data.update_manager.get(0), &box_switcher_tabs);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_switcher_tabs.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_switcher_tabs.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(box_switcher_tabs.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_switcher_tabs.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_switcher_tabs.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_switcher_tabs.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_switcher_tabs.update_interactions({}), true);
	
	box_switcher_tabs.set_size({5, 11});
	ASSERT_EQ(box_switcher_tabs.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_switcher_tabs.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_switcher_tabs.set_position({19, 39});
	ASSERT_EQ(box_switcher_tabs.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_switcher_tabs.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_switcher_tabs.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_switcher_tabs.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_switcher_tabs.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_switcher_tabs.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_switcher_tabs.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_switcher_tabs.move({10, 5});
	ASSERT_EQ(box_switcher_tabs.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_switcher_tabs.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxSwitcherTabs.png"));
}