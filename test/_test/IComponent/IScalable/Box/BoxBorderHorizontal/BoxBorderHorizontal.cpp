#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxBorderHorizontal/BoxBorderHorizontal.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxBorderHorizontal) {
	InitInfoData data{{100, 100}};
	
	ie::BoxBorderHorizontal boxBorderHorizontal{
		{
			ie::makeVector(
				ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
				ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
			),
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxBorderHorizontal.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderHorizontal.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderHorizontal.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderHorizontal.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderHorizontal.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBorderHorizontal.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBorderHorizontal.updateInteractions({}), true);
	
	boxBorderHorizontal.setSize({5, 11});
	ASSERT_EQ(boxBorderHorizontal.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxBorderHorizontal.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxBorderHorizontal.setPosition({19, 39});
	ASSERT_EQ(boxBorderHorizontal.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxBorderHorizontal.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxBorderHorizontal.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxBorderHorizontal.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBorderHorizontal.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBorderHorizontal.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxBorderHorizontal.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxBorderHorizontal.move({10, 5});
	ASSERT_EQ(boxBorderHorizontal.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxBorderHorizontal.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxBorderHorizontal.png"));
}