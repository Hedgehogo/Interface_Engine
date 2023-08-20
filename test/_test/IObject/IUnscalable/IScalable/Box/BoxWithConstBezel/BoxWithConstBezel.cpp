#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/constBezel/boxWithConstBezel.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithConstBezel) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithConstBezel boxWithConstBezel{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Red),
			1
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithConstBezel.getMinSize(), (sf::Vector2f{2, 2}));
	ASSERT_EQ(boxWithConstBezel.getNormalSize(), (sf::Vector2f{2, 2}));
	ASSERT_EQ(boxWithConstBezel.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBezel.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBezel.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBezel.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBezel.updateInteractions({}), true);
	
	boxWithConstBezel.setSize({5, 11});
	ASSERT_EQ(boxWithConstBezel.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithConstBezel.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithConstBezel.setPosition({19, 39});
	ASSERT_EQ(boxWithConstBezel.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithConstBezel.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithConstBezel.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithConstBezel.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstBezel.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstBezel.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithConstBezel.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithConstBezel.move({10, 5});
	ASSERT_EQ(boxWithConstBezel.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithConstBezel.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithConstBezel.png"));
}