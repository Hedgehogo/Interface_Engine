#include "../../../../../../../../../createTestProgram/createTestProgram.hpp"

TEST(FullColor, draw) {
    Program testProgram{
	    new ui::Interface{
            new ui::FullColor{
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
	    new ui::Interface{
            ui::loadFromYaml<ui::IScalable>("../test/tests/7-stage-object/IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/src/test.yaml")
        }
    };

    ASSERT_TRUE((testProgram.renderTexture.getSize() == sf::Vector2u{100, 100}));
    ASSERT_EQ((testProgram.renderTexture.getTexture().copyToImage().getPixel(0, 0)), sf::Color::Red);
}