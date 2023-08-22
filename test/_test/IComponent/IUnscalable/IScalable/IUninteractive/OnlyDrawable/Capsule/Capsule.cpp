#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, Capsule) {
	InitInfoData data{{100, 100}};
	
	ui::Capsule capsule{{sf::Color::Red}, data.makeInitInfo()};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &capsule);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(&capsule.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(capsule.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(capsule.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(capsule.getSize(), sf::Vector2f{});
	ASSERT_EQ(capsule.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(capsule.getPosition(), sf::Vector2f{});
	ASSERT_EQ(capsule.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(capsule.updateInteractions({}), true);
	
	capsule.setSize({5, 11});
	ASSERT_EQ(capsule.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(capsule.getAreaSize(), (sf::Vector2f{5, 11}));
	
	capsule.setPosition({19, 39});
	ASSERT_EQ(capsule.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(capsule.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	capsule.resize({7, 13}, {23, 41});
	ASSERT_EQ(capsule.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(capsule.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(capsule.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(capsule.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	capsule.move({10, 5});
	ASSERT_EQ(capsule.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(capsule.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Capsule.png"));
}