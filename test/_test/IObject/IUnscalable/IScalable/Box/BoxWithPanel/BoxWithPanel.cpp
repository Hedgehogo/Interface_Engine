#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/panel/boxWithPanel.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithPanel) {
	InitInfoData data{{100, 100}};
	
	ui::BoxWithPanel boxWithPanel{
		{
			ui::makeBoxPtr<ui::ConstPanel::Make>(
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
				ui::makeBoxPtr<ui::ISizing2, ui::Sizing2>(sf::Vector2f{10, 10}),
				ui::makeBoxPtr<ui::IPositioning2, ui::Positioning2>(sf::Vector2f{0.5f, 0.5f})
			),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 1);
	ASSERT_EQ(&data.panelManager.get(0), &boxWithPanel.getPanel());
	
	ASSERT_EQ(boxWithPanel.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithPanel.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithPanel.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithPanel.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithPanel.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithPanel.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithPanel.updateInteractions({}), true);
	
	boxWithPanel.setSize({5, 11});
	ASSERT_EQ(boxWithPanel.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithPanel.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithPanel.setPosition({19, 39});
	ASSERT_EQ(boxWithPanel.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithPanel.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithPanel.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithPanel.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithPanel.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithPanel.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithPanel.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithPanel.move({10, 5});
	ASSERT_EQ(boxWithPanel.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithPanel.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	data.panelManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithPanel.png"));
}