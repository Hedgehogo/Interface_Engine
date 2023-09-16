#include <gtest/gtest.h>
#include <IE/Debug/BoxDebug.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxDebug) {
	InitInfoData data{{100, 100}};
	
	ie::BoxDebug boxDebug{
		{ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green)},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(&data.drawManager.get(1), &boxDebug);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxDebug.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxDebug.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxDebug.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxDebug.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxDebug.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxDebug.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxDebug.updateInteractions({}), true);
	
	boxDebug.setSize({5, 11});
	ASSERT_EQ(boxDebug.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxDebug.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxDebug.setPosition({19, 39});
	ASSERT_EQ(boxDebug.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxDebug.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxDebug.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxDebug.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxDebug.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxDebug.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxDebug.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxDebug.move({10, 5});
	ASSERT_EQ(boxDebug.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxDebug.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxDebug.png"));
}