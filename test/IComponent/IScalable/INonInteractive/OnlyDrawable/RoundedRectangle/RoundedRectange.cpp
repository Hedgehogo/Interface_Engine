#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/RoundedRectangle/RoundedRectangle.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, RoundedRectangle) {
	InitInfoData data{{100, 100}};
	
	ie::RoundedRectangle rounded_rectangle{{sf::Color::Red, 2}, data.make_init_info()};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &rounded_rectangle);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&rounded_rectangle.get_render_target(), &data.render_target);
	ASSERT_EQ(rounded_rectangle.get_min_size(), (sf::Vector2f{4, 4}));
	ASSERT_EQ(rounded_rectangle.get_normal_size(), (sf::Vector2f{4, 4}));
	ASSERT_EQ(rounded_rectangle.get_size(), sf::Vector2f{});
	ASSERT_EQ(rounded_rectangle.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(rounded_rectangle.get_position(), sf::Vector2f{});
	ASSERT_EQ(rounded_rectangle.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(rounded_rectangle.handle_event(ie::Event::Pointer(std::numeric_limits<size_t>::max(), {})), true);
	
	rounded_rectangle.set_size({5, 11});
	ASSERT_EQ(rounded_rectangle.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(rounded_rectangle.get_area_size(), (sf::Vector2f{5, 11}));
	
	rounded_rectangle.set_position({19, 39});
	ASSERT_EQ(rounded_rectangle.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(rounded_rectangle.get_area_position(), (sf::Vector2f{19, 39}));
	
	rounded_rectangle.resize({7, 13}, {23, 41});
	ASSERT_EQ(rounded_rectangle.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(rounded_rectangle.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(rounded_rectangle.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(rounded_rectangle.get_area_position(), (sf::Vector2f{23, 41}));
	
	rounded_rectangle.move({10, 5});
	ASSERT_EQ(rounded_rectangle.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(rounded_rectangle.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/RoundedRectangle.png"));
}