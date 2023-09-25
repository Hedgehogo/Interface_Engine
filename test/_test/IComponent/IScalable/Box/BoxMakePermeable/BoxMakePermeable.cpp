#include <gtest/gtest.h>
#include <IE/IComponent/IScalable/Box/BoxMakePermeable/BoxMakePermeable.hpp>
#include <IE/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxMakePermeable) {
	InitInfoData data{{100, 100}};
	
	ie::BoxMakePermeable boxMakePermeable{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green)
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxMakePermeable.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxMakePermeable.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxMakePermeable.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxMakePermeable.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxMakePermeable.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxMakePermeable.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxMakePermeable.updateInteractions({}), false);
	
	boxMakePermeable.setSize({5, 11});
	ASSERT_EQ(boxMakePermeable.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxMakePermeable.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxMakePermeable.setPosition({19, 39});
	ASSERT_EQ(boxMakePermeable.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxMakePermeable.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxMakePermeable.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxMakePermeable.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxMakePermeable.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxMakePermeable.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxMakePermeable.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxMakePermeable.move({10, 5});
	ASSERT_EQ(boxMakePermeable.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxMakePermeable.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxMakePermeable.png"));
}