#include <gtest/gtest.h>
#include "IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BasicBaseButton/ButtonPanel/ButtonPanel.hpp"
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, ButtonPanel) {
	InitInfoData data{{100, 100}};
	
	ie::ButtonPanel buttonPanel{
		{
			ie::makeBoxPtr<ie::Panel::Make>(
				ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
				ie::makeBoxPtr<ie::IHidePanelInteraction, ie::PointingHidePanelInteraction>(),
				ie::makeBoxPtr<ie::ISizing2::Make, ie::Sizing2::Make>(sf::Vector2f{10, 10}),
				ie::makeBoxPtr<ie::IPositioning2::Make, ie::Positioning2::Make>(sf::Vector2f{0.5f, 0.5f})
			),
			ie::makeBoxPtr<ie::IDisplayPanelInteraction, ie::PointingDisplayPanelInteraction>(),
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &buttonPanel);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 1);
	ASSERT_EQ(&data.panelManager.get(0), &buttonPanel.getPanel());
	
	ASSERT_EQ(buttonPanel.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(buttonPanel.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(buttonPanel.getSize(), sf::Vector2f{});
	ASSERT_EQ(buttonPanel.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(buttonPanel.getPosition(), sf::Vector2f{});
	ASSERT_EQ(buttonPanel.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(buttonPanel.updateInteractions({}), true);
	
	buttonPanel.setSize({5, 11});
	ASSERT_EQ(buttonPanel.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(buttonPanel.getAreaSize(), (sf::Vector2f{5, 11}));
	
	buttonPanel.setPosition({19, 39});
	ASSERT_EQ(buttonPanel.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(buttonPanel.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	buttonPanel.resize({7, 13}, {23, 41});
	ASSERT_EQ(buttonPanel.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(buttonPanel.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(buttonPanel.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(buttonPanel.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	buttonPanel.move({10, 5});
	ASSERT_EQ(buttonPanel.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(buttonPanel.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/ButtonPanel.png"));
}