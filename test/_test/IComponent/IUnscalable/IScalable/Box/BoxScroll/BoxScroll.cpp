#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxScroll/BoxScroll.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, BoxScroll) {
	InitInfoData data{{100, 100}};
	
	ie::BoxScroll boxScroll{
		ie::BoxScroll::Make{
			ie::makeBoxPtr<ie::IUnscalable::Make, ie::FullColor::Make>(sf::Color::Green),
			std::make_shared<ie::SRVec2f>(sf::Vector2f{})
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxScroll);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxScroll.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxScroll.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxScroll.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxScroll.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxScroll.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxScroll.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxScroll.updateInteractions({}), true);
	
	boxScroll.setSize({5, 11});
	ASSERT_EQ(boxScroll.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxScroll.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxScroll.setPosition({19, 39});
	ASSERT_EQ(boxScroll.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxScroll.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxScroll.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxScroll.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxScroll.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxScroll.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxScroll.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxScroll.move({10, 5});
	ASSERT_EQ(boxScroll.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxScroll.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxScroll.png"));
}