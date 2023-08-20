#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/renderTexture/boxWithRenderTexture.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithRenderTexture) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithRenderTexture boxWithRenderTexture{
		{ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green)},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxWithRenderTexture);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithRenderTexture.getMinSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxWithRenderTexture.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxWithRenderTexture.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithRenderTexture.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithRenderTexture.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithRenderTexture.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithRenderTexture.updateInteractions({}), true);
	
	boxWithRenderTexture.setSize({5, 11});
	ASSERT_EQ(boxWithRenderTexture.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithRenderTexture.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithRenderTexture.setPosition({19, 39});
	ASSERT_EQ(boxWithRenderTexture.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithRenderTexture.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithRenderTexture.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithRenderTexture.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithRenderTexture.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithRenderTexture.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithRenderTexture.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithRenderTexture.move({10, 5});
	ASSERT_EQ(boxWithRenderTexture.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithRenderTexture.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithRenderTexture.png"));
}