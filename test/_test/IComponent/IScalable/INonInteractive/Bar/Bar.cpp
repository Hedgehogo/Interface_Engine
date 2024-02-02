#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/Bar/Bar.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, Bar) {
	InitInfoData data{{100, 100}};
	
	ie::Bar bar{
		{
			ie::make_box_ptr<ie::INonInteractive::Make, ie::FullColor::Make>(sf::Color::Yellow),
			ie::make_box_ptr<ie::INonInteractive::Make, ie::Capsule::Make>(sf::Color::Red),
			0.2f
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 3);
	ASSERT_EQ(&data.draw_manager.get(0), &bar);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&bar.get_render_target(), &data.render_target);
	ASSERT_EQ(bar.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(bar.get_normal_size(), (sf::Vector2f{0, 1}));
	ASSERT_EQ(bar.get_size(), sf::Vector2f{});
	ASSERT_EQ(bar.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(bar.get_position(), sf::Vector2f{});
	ASSERT_EQ(bar.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(bar.update_interactions({}), true);
	
	bar.set_size({5, 11});
	ASSERT_EQ(bar.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(bar.get_area_size(), (sf::Vector2f{5, 11}));
	
	bar.set_position({19, 39});
	ASSERT_EQ(bar.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(bar.get_area_position(), (sf::Vector2f{19, 39}));
	
	bar.resize({23, 41}, {7, 13});
	ASSERT_EQ(bar.get_size(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(bar.get_area_size(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(bar.get_position(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(bar.get_area_position(), (sf::Vector2f{7, 13}));
	
	bar.move({10, 5});
	ASSERT_EQ(bar.get_position(), (sf::Vector2f{17, 18}));
	ASSERT_EQ(bar.get_area_position(), (sf::Vector2f{17, 18}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Bar.png"));
}