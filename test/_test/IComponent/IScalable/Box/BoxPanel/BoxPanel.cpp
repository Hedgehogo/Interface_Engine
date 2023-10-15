#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxPanel/BoxPanel.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"

TEST(IComponent, BoxPanel) {
	InitInfoData data{{100, 100}};
	
	ie::BoxPanel boxPanel{
		{
			ie::make_box_ptr<ie::ConstPanel::Make>(
				ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red),
				ie::make_box_ptr<ie::ISizing2::Make, ie::Sizing2::Make>(sf::Vector2f{10, 10}),
				ie::make_box_ptr<ie::IPositioning2::Make, ie::Positioning2::Make>(sf::Vector2f{0.5f, 0.5f})
			),
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
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