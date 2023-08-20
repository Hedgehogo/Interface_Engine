#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/interface/interface.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, Interface) {
	InitInfoData data{{100, 100}};
	
	ui::Interface interface{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green)
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &interface);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &interface);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(interface.getDrawManager().size(), 1);
	ASSERT_EQ(interface.getUpdateManager().size(), 0);
	ASSERT_EQ(interface.getInteractionManager().size(), 0);
	ASSERT_EQ(interface.getPanelManager().size(), 0);
	
	ASSERT_EQ(&interface.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(interface.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(interface.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(interface.getSize(), sf::Vector2f{});
	ASSERT_EQ(interface.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(interface.getPosition(), sf::Vector2f{});
	ASSERT_EQ(interface.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(interface.updateInteractions({}), true);
	
	interface.setSize({5, 11});
	ASSERT_EQ(interface.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(interface.getAreaSize(), (sf::Vector2f{5, 11}));
	
	interface.setPosition({19, 39});
	ASSERT_EQ(interface.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(interface.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	interface.resize({7, 13}, {23, 41});
	ASSERT_EQ(interface.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(interface.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(interface.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(interface.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	interface.move({10, 5});
	ASSERT_EQ(interface.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(interface.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Interface.png"));
}