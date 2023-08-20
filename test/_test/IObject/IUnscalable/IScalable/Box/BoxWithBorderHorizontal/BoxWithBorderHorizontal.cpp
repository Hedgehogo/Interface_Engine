#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/border/boxWithBorderHorizontal.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithBorderHorizontal) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithBorderHorizontal boxWithBorderHorizontal{
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
	
	ASSERT_EQ(boxWithBorderHorizontal.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderHorizontal.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderHorizontal.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderHorizontal.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderHorizontal.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderHorizontal.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithBorderHorizontal.updateInteractions({}), true);
	
	boxWithBorderHorizontal.setSize({5, 11});
	ASSERT_EQ(boxWithBorderHorizontal.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithBorderHorizontal.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithBorderHorizontal.setPosition({19, 39});
	ASSERT_EQ(boxWithBorderHorizontal.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithBorderHorizontal.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithBorderHorizontal.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithBorderHorizontal.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBorderHorizontal.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithBorderHorizontal.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithBorderHorizontal.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithBorderHorizontal.move({10, 5});
	ASSERT_EQ(boxWithBorderHorizontal.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithBorderHorizontal.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithBorderHorizontal.png"));
}