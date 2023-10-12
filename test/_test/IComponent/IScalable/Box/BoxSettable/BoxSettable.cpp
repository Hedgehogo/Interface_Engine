#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxSettable/BoxSettable.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxSettable) {
	InitInfoData data{{100, 100}};
	
	ie::BoxSettable boxSettable{
		{ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green)},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxSettable);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &boxSettable);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxSettable.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxSettable.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxSettable.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxSettable.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxSettable.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSettable.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxSettable.updateInteractions({}), true);
	
	boxSettable.setSize({5, 11});
	ASSERT_EQ(boxSettable.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxSettable.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxSettable.setPosition({19, 39});
	ASSERT_EQ(boxSettable.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxSettable.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxSettable.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxSettable.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSettable.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxSettable.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxSettable.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxSettable.move({10, 5});
	ASSERT_EQ(boxSettable.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxSettable.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxSettable.png"));
}