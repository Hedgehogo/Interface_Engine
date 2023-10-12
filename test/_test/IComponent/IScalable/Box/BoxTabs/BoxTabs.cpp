#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxTabs/BoxTabs.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxTabs) {
	InitInfoData data{{100, 100}};
	
	auto value{std::make_shared<ie::Sint>(0)};
	ie::BoxTabs boxTabs{
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
	ASSERT_EQ(&data.drawManager.get(0), &boxTabs);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxTabs.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxTabs.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxTabs.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxTabs.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxTabs.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxTabs.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxTabs.updateInteractions({}), true);
	
	boxTabs.setSize({5, 11});
	ASSERT_EQ(boxTabs.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxTabs.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxTabs.setPosition({19, 39});
	ASSERT_EQ(boxTabs.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxTabs.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxTabs.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxTabs.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxTabs.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxTabs.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxTabs.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxTabs.move({10, 5});
	ASSERT_EQ(boxTabs.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxTabs.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxTabs-0.png"));
	
	value->setValue(1);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxTabs-1.png"));
}