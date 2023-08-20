#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/setableObject/boxWithSetableObject.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithSettableObject) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithSetableObject boxWithSettableObject{
		{ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green)},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxWithSettableObject);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &boxWithSettableObject);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithSettableObject.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithSettableObject.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithSettableObject.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithSettableObject.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithSettableObject.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithSettableObject.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithSettableObject.updateInteractions({}), true);
	
	boxWithSettableObject.setSize({5, 11});
	ASSERT_EQ(boxWithSettableObject.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithSettableObject.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithSettableObject.setPosition({19, 39});
	ASSERT_EQ(boxWithSettableObject.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithSettableObject.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithSettableObject.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithSettableObject.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithSettableObject.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithSettableObject.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithSettableObject.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithSettableObject.move({10, 5});
	ASSERT_EQ(boxWithSettableObject.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithSettableObject.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithSettableObject.png"));
}