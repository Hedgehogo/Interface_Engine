#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Empty/Empty.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, Empty) {
	InitInfoData data{{100, 100}};
	
	ie::Empty empty{{}, data.makeInitInfo()};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &empty);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(&empty.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(empty.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(empty.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(empty.getSize(), sf::Vector2f{});
	ASSERT_EQ(empty.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(empty.getPosition(), sf::Vector2f{});
	ASSERT_EQ(empty.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(empty.updateInteractions({}), false);
	
	empty.setSize({5, 11});
	ASSERT_EQ(empty.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(empty.getAreaSize(), (sf::Vector2f{5, 11}));
	
	empty.setPosition({19, 39});
	ASSERT_EQ(empty.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(empty.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	empty.resize({7, 13}, {23, 41});
	ASSERT_EQ(empty.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(empty.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(empty.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(empty.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	empty.move({10, 5});
	ASSERT_EQ(empty.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(empty.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Empty.png"));
}