#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/constRatioCenter/boxWithConstRatioCenter.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithConstRatioCenter) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithConstRatioCenter boxWithConstRatioCenter{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Blue),
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Yellow),
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 3);
	ASSERT_EQ(&data.drawManager.get(2), &boxWithConstRatioCenter);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithConstRatioCenter.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatioCenter.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatioCenter.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatioCenter.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatioCenter.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatioCenter.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatioCenter.updateInteractions({}), true);
	
	boxWithConstRatioCenter.setSize({5, 11});
	ASSERT_EQ(boxWithConstRatioCenter.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithConstRatioCenter.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithConstRatioCenter.setPosition({19, 39});
	ASSERT_EQ(boxWithConstRatioCenter.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithConstRatioCenter.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithConstRatioCenter.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithConstRatioCenter.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstRatioCenter.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstRatioCenter.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithConstRatioCenter.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithConstRatioCenter.move({10, 5});
	ASSERT_EQ(boxWithConstRatioCenter.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithConstRatioCenter.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithConstRatioCenter.png"));
}