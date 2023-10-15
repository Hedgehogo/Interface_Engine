#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxBorderVertical/BoxBorderVertical.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxBorderVertical) {
	InitInfoData data{{100, 100}};
	
	ie::BoxBorderVertical boxBorderVertical{
		{
			ie::makeVector(
				ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
				ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
			),
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxBorderVertical.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderVertical.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderVertical.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderVertical.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxBorderVertical.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBorderVertical.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxBorderVertical.updateInteractions({}), true);
	
	boxBorderVertical.setSize({5, 11});
	ASSERT_EQ(boxBorderVertical.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxBorderVertical.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxBorderVertical.setPosition({19, 39});
	ASSERT_EQ(boxBorderVertical.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxBorderVertical.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxBorderVertical.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxBorderVertical.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBorderVertical.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxBorderVertical.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxBorderVertical.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxBorderVertical.move({10, 5});
	ASSERT_EQ(boxBorderVertical.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxBorderVertical.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxBorderVertical.png"));
}