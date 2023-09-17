#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxSwitch/BoxSwitch.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxSwitch) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ie::Sbool>(false);
	ie::BoxSwitch boxSwitch{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
			value
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxSwitch);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxSwitch.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitch.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitch.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitch.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxSwitch.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitch.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSwitch.updateInteractions({}), true);
	
	boxSwitch.setSize({5, 11});
	ASSERT_EQ(boxSwitch.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxSwitch.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxSwitch.setPosition({19, 39});
	ASSERT_EQ(boxSwitch.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxSwitch.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxSwitch.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxSwitch.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitch.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSwitch.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxSwitch.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxSwitch.move({10, 5});
	ASSERT_EQ(boxSwitch.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxSwitch.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSwitch-false.png"));
	
	value->setValue(true);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSwitch-true.png"));
}