#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxAlternative/BoxAlternative.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxAlternative) {
	InitInfoData data{{100, 100}};
	
	ie::BoxAlternative boxAlternative{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::Capsule::Make>(sf::Color::Green),
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxAlternative.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxAlternative.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxAlternative.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxAlternative.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxAlternative.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxAlternative.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxAlternative.updateInteractions({}), true);
	
	boxAlternative.setSize({5, 11});
	ASSERT_EQ(boxAlternative.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxAlternative.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxAlternative.setPosition({19, 39});
	ASSERT_EQ(boxAlternative.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxAlternative.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxAlternative.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxAlternative.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxAlternative.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxAlternative.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxAlternative.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxAlternative.move({10, 5});
	ASSERT_EQ(boxAlternative.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxAlternative.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxAlternative.png"));
}