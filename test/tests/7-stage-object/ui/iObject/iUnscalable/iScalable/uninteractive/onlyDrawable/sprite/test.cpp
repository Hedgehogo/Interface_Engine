#include "../../../../../../../../../create_test_program/create_test_program.hpp"

TEST(Sprite, draw) {
    sf::Texture test_texture;
    test_texture.loadFromFile("../test/tests/7-stage-object/IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/Sprite/src/gigachad.jpg");

    Program test_program{
        new ie::Interface{
            new ie::Sprite{
                test_texture
            }
        }
    };

    ASSERT_TRUE(test_program.render_texture.getTexture() == test_texture);
}

TEST(Sprite, YAML) {
    Program test_program{
	    new ie::Interface{
            ie::load_from_yaml<ie::IScalable>("../test/tests/7-stage-object/IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/Sprite/src/test.yaml")
        }
    };

	ASSERT_TRUE((test_program.interface->get_min_size() == sf::Vector2f{5, 5}));
	ASSERT_TRUE((test_program.interface->get_normal_size() == sf::Vector2f{10, 10}));

    sf::Image test_image;
    test_image.loadFromFile("../test/tests/7-stage-object/IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/Sprite/src/gigachad.jpg");

    sf::Image render_image{test_program.render_texture.getTexture().copyToImage()};

    ASSERT_TRUE((render_image.get_size() == sf::Vector2u{10, 10}));

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            ASSERT_TRUE((render_image.get_pixel(x, y) == test_image.get_pixel(x, y)));
        }
    }
}
