#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/makePermeable/boxMakePermeable.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxMakePermeable) {
	InitInfoData data{{100, 100}};
	
	ui::BoxMakePermeable boxMakePermeable{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green)
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