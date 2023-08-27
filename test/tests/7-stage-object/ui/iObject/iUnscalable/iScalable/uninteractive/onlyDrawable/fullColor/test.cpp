#include "../../../../../../../../../createTestProgram/createTestProgram.hpp"

TEST(FullColor, draw) {
    Program testProgram{
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

    ASSERT_TRUE(testProgram.renderTexture.getTexture() == texture.getTexture());
}

TEST(FullColor, YAML) {
    Program testProgram{
	    new ie::Interface{
            ie::loadFromYaml<ie::IScalable>("../test/tests/7-stage-object/IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/src/test.yaml")
        }
    };

    ASSERT_TRUE((testProgram.renderTexture.getSize() == sf::Vector2u{100, 100}));
    ASSERT_EQ((testProgram.renderTexture.getTexture().copyToImage().getPixel(0, 0)), sf::Color::Red);
}