#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/switcher/boxSwitcher.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxSwitcher) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ui::Sbool>(false);
	ui::BoxSwitcher boxSwitcher{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
			value
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxSwitcher);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxSwitcher.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcher.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcher.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcher.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcher.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcher.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitcher.updateInteractions({}), true);
	
	boxSwitcher.setSize({5, 11});
	ASSERT_EQ(boxSwitcher.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxSwitcher.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxSwitcher.setPosition({19, 39});
	ASSERT_EQ(boxSwitcher.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxSwitcher.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxSwitcher.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxSwitcher.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitcher.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitcher.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxSwitcher.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxSwitcher.move({10, 5});
	ASSERT_EQ(boxSwitcher.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxSwitcher.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSwitcher-false.png"));
	
	value->setValue(true);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSwitcher-true.png"));
}