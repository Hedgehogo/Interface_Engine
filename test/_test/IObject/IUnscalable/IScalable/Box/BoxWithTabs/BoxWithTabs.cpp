#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/tabs/boxWithTabs.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithTabs) {
	InitInfoData data{{100, 100}};
	
	auto value{std::make_shared<ui::Sint>(0)};
	ui::BoxWithTabs boxWithTabs{
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
	ASSERT_EQ(&data.drawManager.get(0), &boxWithTabs);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithTabs.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithTabs.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithTabs.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithTabs.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithTabs.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithTabs.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithTabs.updateInteractions({}), true);
	
	boxWithTabs.setSize({5, 11});
	ASSERT_EQ(boxWithTabs.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithTabs.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithTabs.setPosition({19, 39});
	ASSERT_EQ(boxWithTabs.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithTabs.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithTabs.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithTabs.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithTabs.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithTabs.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithTabs.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithTabs.move({10, 5});
	ASSERT_EQ(boxWithTabs.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithTabs.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithTabs-0.png"));
	
	value->setValue(1);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithTabs-1.png"));
}