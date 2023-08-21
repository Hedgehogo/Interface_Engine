#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/RoundedRectangle/RoundedRectangle.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IObject, RoundedRectangle) {
	InitInfoData data{{100, 100}};
	
	ui::RoundedRectangle roundedRectangle{{sf::Color::Red, 2}, data.makeInitInfo()};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &roundedRectangle);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(&roundedRectangle.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(roundedRectangle.getMinSize(), (sf::Vector2f{4, 4}));
	ASSERT_EQ(roundedRectangle.getNormalSize(), (sf::Vector2f{4, 4}));
	ASSERT_EQ(roundedRectangle.getSize(), sf::Vector2f{});
	ASSERT_EQ(roundedRectangle.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(roundedRectangle.getPosition(), sf::Vector2f{});
	ASSERT_EQ(roundedRectangle.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(roundedRectangle.updateInteractions({}), true);
	
	roundedRectangle.setSize({5, 11});
	ASSERT_EQ(roundedRectangle.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(roundedRectangle.getAreaSize(), (sf::Vector2f{5, 11}));
	
	roundedRectangle.setPosition({19, 39});
	ASSERT_EQ(roundedRectangle.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(roundedRectangle.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	roundedRectangle.resize({7, 13}, {23, 41});
	ASSERT_EQ(roundedRectangle.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(roundedRectangle.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(roundedRectangle.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(roundedRectangle.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	roundedRectangle.move({10, 5});
	ASSERT_EQ(roundedRectangle.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(roundedRectangle.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/RoundedRectangle.png"));
}