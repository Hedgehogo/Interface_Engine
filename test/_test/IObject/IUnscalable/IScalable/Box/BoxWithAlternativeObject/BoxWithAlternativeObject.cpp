#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/alternativeObject/boxWithAlternativeObject.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/capsule/capsule.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithAlternativeObject) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithAlternativeObject boxWithAlternativeObject{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::Capsule::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red)
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithAlternativeObject.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithAlternativeObject.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxWithAlternativeObject.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithAlternativeObject.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithAlternativeObject.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithAlternativeObject.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithAlternativeObject.updateInteractions({}), true);
	
	boxWithAlternativeObject.setSize({5, 11});
	ASSERT_EQ(boxWithAlternativeObject.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithAlternativeObject.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithAlternativeObject.setPosition({19, 39});
	ASSERT_EQ(boxWithAlternativeObject.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithAlternativeObject.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithAlternativeObject.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithAlternativeObject.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithAlternativeObject.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithAlternativeObject.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithAlternativeObject.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithAlternativeObject.move({10, 5});
	ASSERT_EQ(boxWithAlternativeObject.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithAlternativeObject.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithAlternativeObject.png"));
}