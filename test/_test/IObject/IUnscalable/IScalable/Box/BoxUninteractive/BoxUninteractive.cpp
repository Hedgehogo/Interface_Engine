#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/uninteractive/boxUninteractive.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxUninteractive) {
	InitInfoData data{{100, 100}};
	
	ui::BoxUninteractive boxUninteractive{
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
	
	ASSERT_EQ(boxUninteractive.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxUninteractive.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxUninteractive.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxUninteractive.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxUninteractive.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxUninteractive.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxUninteractive.updateInteractions({}), true);
	
	boxUninteractive.setSize({5, 11});
	ASSERT_EQ(boxUninteractive.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxUninteractive.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxUninteractive.setPosition({19, 39});
	ASSERT_EQ(boxUninteractive.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxUninteractive.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxUninteractive.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxUninteractive.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxUninteractive.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxUninteractive.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxUninteractive.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxUninteractive.move({10, 5});
	ASSERT_EQ(boxUninteractive.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxUninteractive.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxUninteractive.png"));
}