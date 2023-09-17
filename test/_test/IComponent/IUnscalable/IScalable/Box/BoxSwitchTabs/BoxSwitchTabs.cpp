#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxSwitchTabs/BoxSwitchTabs.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxSwitchTabs) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ie::Suint>(0);
	ie::BoxSwitchTabs boxSwitchTabs{
		{
			ie::makeVector(
				ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
				ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
			),
			value
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxSwitchTabs);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxSwitchTabs.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitchTabs.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitchTabs.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitchTabs.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitchTabs.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitchTabs.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitchTabs.updateInteractions({}), true);
	
	boxSwitchTabs.setSize({5, 11});
	ASSERT_EQ(boxSwitchTabs.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxSwitchTabs.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxSwitchTabs.setPosition({19, 39});
	ASSERT_EQ(boxSwitchTabs.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxSwitchTabs.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxSwitchTabs.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxSwitchTabs.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitchTabs.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitchTabs.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxSwitchTabs.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxSwitchTabs.move({10, 5});
	ASSERT_EQ(boxSwitchTabs.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxSwitchTabs.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSwitchTabs-0.png"));
	
	value->setValue(1);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSwitchTabs-1.png"));
}