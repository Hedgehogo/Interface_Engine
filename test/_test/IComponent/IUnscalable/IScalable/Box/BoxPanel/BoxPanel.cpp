#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxPanel/BoxPanel.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxPanel) {
	InitInfoData data{{100, 100}};
	
	ui::BoxPanel boxPanel{
		{
			ui::makeBoxPtr<ui::ConstPanel::Make>(
				ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
				ui::makeBoxPtr<ui::ISizing2::Make, ui::Sizing2::Make>(sf::Vector2f{10, 10}),
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
	ASSERT_EQ(&data.panelManager.get(0), &boxPanel.getPanel());
	
	ASSERT_EQ(boxPanel.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxPanel.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxPanel.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxPanel.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxPanel.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxPanel.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxPanel.updateInteractions({}), true);
	
	boxPanel.setSize({5, 11});
	ASSERT_EQ(boxPanel.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxPanel.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxPanel.setPosition({19, 39});
	ASSERT_EQ(boxPanel.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxPanel.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxPanel.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxPanel.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxPanel.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxPanel.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxPanel.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxPanel.move({10, 5});
	ASSERT_EQ(boxPanel.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxPanel.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	data.panelManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxPanel.png"));
}