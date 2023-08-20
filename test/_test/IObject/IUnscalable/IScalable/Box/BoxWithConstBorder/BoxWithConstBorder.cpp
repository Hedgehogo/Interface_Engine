#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/constBorder/boxWithConstBorder.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithConstBorder) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithConstBorder boxWithConstBorder{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
			2,
			ui::Side::left
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithConstBorder.getMinSize(), (sf::Vector2f{2, 0}));
	ASSERT_EQ(boxWithConstBorder.getNormalSize(), (sf::Vector2f{2, 0}));
	ASSERT_EQ(boxWithConstBorder.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBorder.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBorder.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBorder.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithConstBorder.updateInteractions({}), true);
	
	boxWithConstBorder.setSize({5, 11});
	ASSERT_EQ(boxWithConstBorder.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithConstBorder.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithConstBorder.setPosition({19, 39});
	ASSERT_EQ(boxWithConstBorder.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithConstBorder.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithConstBorder.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithConstBorder.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstBorder.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithConstBorder.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithConstBorder.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithConstBorder.move({10, 5});
	ASSERT_EQ(boxWithConstBorder.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithConstBorder.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithConstBorder.png"));
}