#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxBackground/BoxBackground.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, BoxBackground) {
	InitInfoData data{{100, 100}};
	
	ie::BoxBackground boxBackground{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::Capsule::Make>(sf::Color::Green),
			ie::makeBoxPtr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Red)
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxBackground.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxBackground.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxBackground.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxBackground.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxBackground.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBackground.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBackground.updateInteractions({}), true);
	
	boxBackground.setSize({5, 11});
	ASSERT_EQ(boxBackground.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxBackground.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxBackground.setPosition({19, 39});
	ASSERT_EQ(boxBackground.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxBackground.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxBackground.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxBackground.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBackground.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBackground.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxBackground.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxBackground.move({10, 5});
	ASSERT_EQ(boxBackground.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxBackground.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxBackground.png"));
}