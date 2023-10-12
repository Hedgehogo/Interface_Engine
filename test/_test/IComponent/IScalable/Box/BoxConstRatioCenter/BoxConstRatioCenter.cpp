#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxConstRatioCenter/BoxConstRatioCenter.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxConstRatioCenter) {
	InitInfoData data{{100, 100}};
	
	ie::BoxConstRatioCenter boxConstRatioCenter{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Blue),
			ie::makeBoxPtr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Yellow),
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 3);
	ASSERT_EQ(&data.drawManager.get(2), &boxConstRatioCenter);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxConstRatioCenter.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatioCenter.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatioCenter.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatioCenter.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatioCenter.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatioCenter.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatioCenter.updateInteractions({}), true);
	
	boxConstRatioCenter.setSize({5, 11});
	ASSERT_EQ(boxConstRatioCenter.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxConstRatioCenter.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxConstRatioCenter.setPosition({19, 39});
	ASSERT_EQ(boxConstRatioCenter.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxConstRatioCenter.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxConstRatioCenter.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxConstRatioCenter.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstRatioCenter.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstRatioCenter.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxConstRatioCenter.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxConstRatioCenter.move({10, 5});
	ASSERT_EQ(boxConstRatioCenter.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxConstRatioCenter.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxConstRatioCenter.png"));
}