#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/changeableObjects/boxWithChangeableObjects.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithChangeableObjects) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ui::Suint>(0);
	ui::BoxWithChangeableObjects boxWithChangeableObjects{
		{
			ui::makeVector(
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red)
			),
			value
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxWithChangeableObjects);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithChangeableObjects.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithChangeableObjects.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithChangeableObjects.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithChangeableObjects.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithChangeableObjects.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithChangeableObjects.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithChangeableObjects.updateInteractions({}), true);
	
	boxWithChangeableObjects.setSize({5, 11});
	ASSERT_EQ(boxWithChangeableObjects.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithChangeableObjects.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithChangeableObjects.setPosition({19, 39});
	ASSERT_EQ(boxWithChangeableObjects.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithChangeableObjects.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithChangeableObjects.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithChangeableObjects.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithChangeableObjects.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithChangeableObjects.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithChangeableObjects.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithChangeableObjects.move({10, 5});
	ASSERT_EQ(boxWithChangeableObjects.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithChangeableObjects.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithChangeableObjects-0.png"));
	
	value->setValue(1);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithChangeableObjects-1.png"));
}