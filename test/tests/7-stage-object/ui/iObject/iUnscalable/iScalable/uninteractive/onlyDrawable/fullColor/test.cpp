#include "../../../../../../../../../create_test_program/create_test_program.hpp"

TEST(FullColor, draw) {
    Program test_program{
	    new ie::Interface{
            new ie::FullColor{
                {255, 0, 0}
            }
        },
        {100, 100}
    };

    sf::RenderTexture texture;
    texture.create(100, 100);
    texture.clear({255, 0, 0});

    ASSERT_TRUE(test_program.render_texture.getTexture() == texture.getTexture());
}

TEST(FullColor, YAML) {
    Program test_program{
	    new ie::Interface{
            ie::load_from_yaml<ie::IScalable>("../test/tests/7-stage-object/IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/src/test.yaml")
        }
    };

    ASSERT_TRUE((test_program.render_texture.get_size() == sf::Vector2u{100, 100}));
    ASSERT_EQ((test_program.render_texture.getTexture().copyToImage().get_pixel(0, 0)), sf::Color::Red);
}