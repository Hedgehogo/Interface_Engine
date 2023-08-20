#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/background/boxWithBackground.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/capsule/capsule.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithBackground) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithBackground boxWithBackground{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::Capsule::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Red)
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithBackground.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBackground.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxWithBackground.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBackground.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBackground.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBackground.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBackground.updateInteractions({}), true);
	
	boxWithBackground.setSize({5, 11});
	ASSERT_EQ(boxWithBackground.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithBackground.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithBackground.setPosition({19, 39});
	ASSERT_EQ(boxWithBackground.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithBackground.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithBackground.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithBackground.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBackground.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBackground.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithBackground.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithBackground.move({10, 5});
	ASSERT_EQ(boxWithBackground.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithBackground.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithBackground.png"));
}