#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxShader/BoxShader.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "_image_equal/image_equal.hpp"

TEST(IComponent, BoxShader) {
	InitInfoData data{{100, 100}};
	
	auto shader = new sf::Shader{};
	shader->loadFromFile("test-src/BoxShader.glsl", sf::Shader::Type::Fragment);
	ie::BoxShader box_shader{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::Capsule::Make>(sf::Color::Green),
			new sf::Shader{},
			ie::BoxShader::Transmission::Texture
		},
		data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 1);
	ASSERT_EQ(&data.draw_manager.get(0), &box_shader);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_shader.get_min_size(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(box_shader.get_normal_size(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(box_shader.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_shader.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_shader.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_shader.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_shader.update_interactions(ie::Event::Touch(std::numeric_limits<size_t>::max(), {})), true);
	
	box_shader.set_size({5, 11});
	ASSERT_EQ(box_shader.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_shader.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_shader.set_position({19, 39});
	ASSERT_EQ(box_shader.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_shader.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_shader.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_shader.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_shader.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_shader.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_shader.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_shader.move({10, 5});
	ASSERT_EQ(box_shader.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_shader.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxShader.png"));
}