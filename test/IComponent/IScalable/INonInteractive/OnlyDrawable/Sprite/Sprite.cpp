#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Sprite/Sprite.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, Sprite) {
	InitInfoData data{{100, 100}};
	
	sf::Texture texture{};
	texture.loadFromFile("../../example-resources/image.png");
	ie::Sprite sprite{{texture}, data.make_init_info()};
	data.update_manager.update();
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &sprite);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(&sprite.get_render_target(), &data.render_target);
	ASSERT_EQ(sprite.get_min_size(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(sprite.get_normal_size(), (sf::Vector2f{112, 112}));
	ASSERT_EQ(sprite.get_size(), (sf::Vector2f{112, 112}));
	ASSERT_EQ(sprite.get_area_size(), (sf::Vector2f{112, 112}));
	ASSERT_EQ(sprite.get_position(), sf::Vector2f{});
	ASSERT_EQ(sprite.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(sprite.handle_event(ie::Event::Pointer({std::numeric_limits<size_t>::max(), {}})), true);
	
	sprite.set_size({5, 11});
	ASSERT_EQ(sprite.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(sprite.get_area_size(), (sf::Vector2f{5, 11}));
	
	sprite.set_position({19, 39});
	ASSERT_EQ(sprite.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(sprite.get_area_position(), (sf::Vector2f{19, 39}));
	
	sprite.resize({7, 13}, {23, 41});
	ASSERT_EQ(sprite.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(sprite.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(sprite.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(sprite.get_area_position(), (sf::Vector2f{23, 41}));
	
	sprite.move({10, 5});
	ASSERT_EQ(sprite.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(sprite.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Sprite.png", 0.01));
}