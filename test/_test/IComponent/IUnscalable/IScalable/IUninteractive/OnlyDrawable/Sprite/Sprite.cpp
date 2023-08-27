#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Sprite/Sprite.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, Sprite) {
	InitInfoData data{{100, 100}};
	
	sf::Texture texture{};
	texture.loadFromFile("../../example-resources/image.png");
	ie::Sprite sprite{{texture}, data.makeInitInfo()};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &sprite);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(&sprite.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(sprite.getMinSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(sprite.getNormalSize(), (sf::Vector2f{112, 112}));
	ASSERT_EQ(sprite.getSize(), (sf::Vector2f{112, 112}));
	ASSERT_EQ(sprite.getAreaSize(), (sf::Vector2f{112, 112}));
	ASSERT_EQ(sprite.getPosition(), sf::Vector2f{});
	ASSERT_EQ(sprite.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(sprite.updateInteractions({}), true);
	
	sprite.setSize({5, 11});
	ASSERT_EQ(sprite.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(sprite.getAreaSize(), (sf::Vector2f{5, 11}));
	
	sprite.setPosition({19, 39});
	ASSERT_EQ(sprite.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(sprite.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	sprite.resize({7, 13}, {23, 41});
	ASSERT_EQ(sprite.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(sprite.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(sprite.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(sprite.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	sprite.move({10, 5});
	ASSERT_EQ(sprite.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(sprite.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Sprite.png"));
}