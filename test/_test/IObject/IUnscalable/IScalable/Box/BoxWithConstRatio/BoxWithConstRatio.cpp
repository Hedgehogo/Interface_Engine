#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/constRatio/boxWithConstRatio.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithConstRatio) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithConstRatio boxWithConstRatio{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Blue)
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 3);
	ASSERT_EQ(&data.drawManager.get(2), &boxWithConstRatio);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithConstRatio.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatio.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatio.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatio.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatio.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatio.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstRatio.updateInteractions({}), true);
	
	boxWithConstRatio.setSize({5, 11});
	ASSERT_EQ(boxWithConstRatio.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithConstRatio.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithConstRatio.setPosition({19, 39});
	ASSERT_EQ(boxWithConstRatio.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithConstRatio.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithConstRatio.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithConstRatio.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstRatio.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstRatio.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithConstRatio.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithConstRatio.move({10, 5});
	ASSERT_EQ(boxWithConstRatio.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithConstRatio.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithConstRatio.png"));
}