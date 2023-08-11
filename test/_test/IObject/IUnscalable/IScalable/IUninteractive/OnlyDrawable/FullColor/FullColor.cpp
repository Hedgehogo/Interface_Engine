#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>

TEST(IObject, FullColor) {
	InitInfoData data{{100, 100}};
	
	ui::FullColor fullColor{ui::FullColor::Make{sf::Color::Red}, data.makeInitInfo()};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &fullColor);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(&fullColor.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(fullColor.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(fullColor.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(fullColor.getSize(), sf::Vector2f{});
	ASSERT_EQ(fullColor.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(fullColor.getPosition(), sf::Vector2f{});
	ASSERT_EQ(fullColor.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(fullColor.updateInteractions({}), true);
	
	fullColor.setSize({5, 11});
	ASSERT_EQ(fullColor.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(fullColor.getAreaSize(), (sf::Vector2f{5, 11}));
	
	fullColor.setPosition({19, 39});
	ASSERT_EQ(fullColor.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(fullColor.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	fullColor.resize({7, 13}, {23, 41});
	ASSERT_EQ(fullColor.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(fullColor.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(fullColor.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(fullColor.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	fullColor.move({10, 5});
	ASSERT_EQ(fullColor.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(fullColor.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	fullColor.draw();
	ASSERT_TRUE(data.renderEqualWithSave("images/FullColor.png"));
}