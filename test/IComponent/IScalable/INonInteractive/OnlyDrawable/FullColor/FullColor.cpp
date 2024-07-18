#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, FullColor) {
	InitInfoData data{{100, 100}};
	
	ie::FullColor full_color{{sf::Color::Red}, data.make_init_info()};
	data.update_manager.update();
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &full_color);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&full_color.get_render_target(), &data.render_target);
	ASSERT_EQ(full_color.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(full_color.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(full_color.get_size(), sf::Vector2f{});
	ASSERT_EQ(full_color.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(full_color.get_position(), sf::Vector2f{});
	ASSERT_EQ(full_color.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(full_color.handle_event(ie::Event::Pointer({})), true);
	
	full_color.set_size({5, 11});
	ASSERT_EQ(full_color.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(full_color.get_area_size(), (sf::Vector2f{5, 11}));
	
	full_color.set_position({19, 39});
	ASSERT_EQ(full_color.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(full_color.get_area_position(), (sf::Vector2f{19, 39}));
	
	full_color.resize({7, 13}, {23, 41});
	ASSERT_EQ(full_color.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(full_color.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(full_color.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(full_color.get_area_position(), (sf::Vector2f{23, 41}));
	
	full_color.move({10, 5});
	ASSERT_EQ(full_color.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(full_color.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/FullColor.png"));
}