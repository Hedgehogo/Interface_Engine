#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxConstRatio/BoxConstRatio.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxConstRatio) {
	InitInfoData data{{100, 100}};
	
	ie::BoxConstRatio boxConstRatio{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
			ie::makeBoxPtr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Blue)
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 3);
	ASSERT_EQ(&data.drawManager.get(2), &boxConstRatio);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxConstRatio.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatio.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatio.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatio.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatio.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatio.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxConstRatio.updateInteractions({}), true);
	
	boxConstRatio.setSize({5, 11});
	ASSERT_EQ(boxConstRatio.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxConstRatio.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxConstRatio.setPosition({19, 39});
	ASSERT_EQ(boxConstRatio.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxConstRatio.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxConstRatio.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxConstRatio.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstRatio.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxConstRatio.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxConstRatio.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxConstRatio.move({10, 5});
	ASSERT_EQ(boxConstRatio.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxConstRatio.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxConstRatio.png"));
}