#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/border/boxWithBorderVertical.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithBorderVertical) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithBorderVertical boxWithBorderVertical{
		{
			ui::makeVector(
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red)
			),
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithBorderVertical.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderVertical.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderVertical.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderVertical.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderVertical.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderVertical.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderVertical.updateInteractions({}), true);
	
	boxWithBorderVertical.setSize({5, 11});
	ASSERT_EQ(boxWithBorderVertical.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithBorderVertical.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithBorderVertical.setPosition({19, 39});
	ASSERT_EQ(boxWithBorderVertical.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithBorderVertical.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithBorderVertical.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithBorderVertical.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBorderVertical.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBorderVertical.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithBorderVertical.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithBorderVertical.move({10, 5});
	ASSERT_EQ(boxWithBorderVertical.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithBorderVertical.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithBorderVertical.png"));
}