#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/interactive/simple/button/buttonWithPanel/buttonWithPanel.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, ButtonWithPanel) {
	InitInfoData data{{100, 100}};
	
	ui::ButtonWithPanel buttonWithPanel{
		{
			ui::makeBoxPtr<ui::Panel::Make>(
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
				ui::makeBoxPtr<ui::IHidePanelInteraction, ui::PointingHidePanelInteraction>(),
				ui::makeBoxPtr<ui::ISizing2, ui::Sizing2>(sf::Vector2f{10, 10}),
				ui::makeBoxPtr<ui::IPositioning2, ui::Positioning2>(sf::Vector2f{0.5f, 0.5f})
			),
			ui::makeBoxPtr<ui::IDisplayPanelInteraction, ui::PointingDisplayPanelInteraction>(),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &buttonWithPanel);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 1);
	ASSERT_EQ(&data.panelManager.get(0), &buttonWithPanel.getPanel());
	
	ASSERT_EQ(buttonWithPanel.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(buttonWithPanel.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(buttonWithPanel.getSize(), sf::Vector2f{});
	ASSERT_EQ(buttonWithPanel.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(buttonWithPanel.getPosition(), sf::Vector2f{});
	ASSERT_EQ(buttonWithPanel.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(buttonWithPanel.updateInteractions({}), true);
	
	buttonWithPanel.setSize({5, 11});
	ASSERT_EQ(buttonWithPanel.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(buttonWithPanel.getAreaSize(), (sf::Vector2f{5, 11}));
	
	buttonWithPanel.setPosition({19, 39});
	ASSERT_EQ(buttonWithPanel.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(buttonWithPanel.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	buttonWithPanel.resize({7, 13}, {23, 41});
	ASSERT_EQ(buttonWithPanel.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(buttonWithPanel.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(buttonWithPanel.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(buttonWithPanel.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	buttonWithPanel.move({10, 5});
	ASSERT_EQ(buttonWithPanel.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(buttonWithPanel.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/ButtonWithPanel.png"));
}