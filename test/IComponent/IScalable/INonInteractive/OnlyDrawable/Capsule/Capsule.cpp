#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, Capsule) {
	InitInfoData data{{100, 100}};
	
	ie::Capsule capsule{{sf::Color::Red}, data.make_init_info()};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &capsule);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&capsule.get_render_target(), &data.render_target);
	ASSERT_EQ(capsule.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(capsule.get_normal_size(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(capsule.get_size(), sf::Vector2f{});
	ASSERT_EQ(capsule.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(capsule.get_position(), sf::Vector2f{});
	ASSERT_EQ(capsule.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(capsule.update_interactions(ie::Event::Touch(std::numeric_limits<size_t>::max(), {})), true);
	
	capsule.set_size({5, 11});
	ASSERT_EQ(capsule.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(capsule.get_area_size(), (sf::Vector2f{5, 11}));
	
	capsule.set_position({19, 39});
	ASSERT_EQ(capsule.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(capsule.get_area_position(), (sf::Vector2f{19, 39}));
	
	capsule.resize({7, 13}, {23, 41});
	ASSERT_EQ(capsule.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(capsule.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(capsule.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(capsule.get_area_position(), (sf::Vector2f{23, 41}));
	
	capsule.move({10, 5});
	ASSERT_EQ(capsule.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(capsule.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Capsule.png"));
}