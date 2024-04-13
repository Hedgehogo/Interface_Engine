#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Empty/Empty.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "_image_equal/image_equal.hpp"

TEST(IComponent, Empty) {
	InitInfoData data{{100, 100}};
	
	ie::Empty empty{{}, data.make_init_info()};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &empty);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&empty.get_render_target(), &data.render_target);
	ASSERT_EQ(empty.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(empty.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(empty.get_size(), sf::Vector2f{});
	ASSERT_EQ(empty.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(empty.get_position(), sf::Vector2f{});
	ASSERT_EQ(empty.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(empty.update_interactions(ie::Event::Touch(std::numeric_limits<size_t>::max(), {})), false);
	
	empty.set_size({5, 11});
	ASSERT_EQ(empty.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(empty.get_area_size(), (sf::Vector2f{5, 11}));
	
	empty.set_position({19, 39});
	ASSERT_EQ(empty.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(empty.get_area_position(), (sf::Vector2f{19, 39}));
	
	empty.resize({7, 13}, {23, 41});
	ASSERT_EQ(empty.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(empty.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(empty.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(empty.get_area_position(), (sf::Vector2f{23, 41}));
	
	empty.move({10, 5});
	ASSERT_EQ(empty.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(empty.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Empty.png"));
}