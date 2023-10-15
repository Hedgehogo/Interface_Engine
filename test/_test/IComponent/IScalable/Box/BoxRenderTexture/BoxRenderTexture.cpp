#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxRenderTexture/BoxRenderTexture.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxRenderTexture) {
	InitInfoData data{{100, 100}};
	
	ie::BoxRenderTexture boxRenderTexture{
		{ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green)},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxRenderTexture);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxRenderTexture.getMinSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxRenderTexture.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxRenderTexture.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxRenderTexture.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxRenderTexture.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxRenderTexture.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxRenderTexture.updateInteractions({}), true);
	
	boxRenderTexture.setSize({5, 11});
	ASSERT_EQ(boxRenderTexture.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxRenderTexture.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxRenderTexture.setPosition({19, 39});
	ASSERT_EQ(boxRenderTexture.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxRenderTexture.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxRenderTexture.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxRenderTexture.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxRenderTexture.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxRenderTexture.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxRenderTexture.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxRenderTexture.move({10, 5});
	ASSERT_EQ(boxRenderTexture.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxRenderTexture.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxRenderTexture.png"));
}