#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/scroll/boxScroll.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxScroll) {
	InitInfoData data{{100, 100}};
	
	ui::BoxScroll boxScroll{
		ui::BoxScroll::Make{
			ui::makeBoxPtr<ui::IUnscalable::Make, ui::FullColor::Make>(sf::Color::Green),
			std::make_shared<ui::SRVec2f>(sf::Vector2f{})
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