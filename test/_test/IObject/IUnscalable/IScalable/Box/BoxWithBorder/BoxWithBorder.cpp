#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/border/boxWithBorder.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithBorder) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithBorder boxWithBorder{
		{
			ui::makeVector(
				ui::makeVector(
					ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
					ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red)
				),
				ui::makeVector(
					ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Blue),
					ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Yellow)
				)
			)
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 4);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithBorder.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorder.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorder.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorder.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorder.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorder.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorder.updateInteractions({}), true);
	
	boxWithBorder.setSize({5, 11});
	ASSERT_EQ(boxWithBorder.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithBorder.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithBorder.setPosition({19, 39});
	ASSERT_EQ(boxWithBorder.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithBorder.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithBorder.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithBorder.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBorder.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBorder.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithBorder.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithBorder.move({10, 5});
	ASSERT_EQ(boxWithBorder.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithBorder.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithBorder.png"));
}