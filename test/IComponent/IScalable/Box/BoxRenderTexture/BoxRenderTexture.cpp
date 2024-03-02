#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxRenderTexture/BoxRenderTexture.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "image_equal/image_equal.hpp"

TEST(IComponent, BoxRenderTexture) {
	InitInfoData data{{100, 100}};
	
	ie::BoxRenderTexture box_render_texture{
		{ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green)},
		data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &box_render_texture);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_render_texture.get_min_size(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(box_render_texture.get_normal_size(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(box_render_texture.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_render_texture.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_render_texture.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_render_texture.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_render_texture.update_interactions({}), true);
	
	box_render_texture.set_size({5, 11});
	ASSERT_EQ(box_render_texture.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_render_texture.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_render_texture.set_position({19, 39});
	ASSERT_EQ(box_render_texture.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_render_texture.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_render_texture.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_render_texture.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_render_texture.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_render_texture.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_render_texture.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_render_texture.move({10, 5});
	ASSERT_EQ(box_render_texture.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_render_texture.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxRenderTexture.png"));
}