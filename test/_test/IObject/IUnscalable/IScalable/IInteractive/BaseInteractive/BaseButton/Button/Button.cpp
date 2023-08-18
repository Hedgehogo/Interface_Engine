#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/interactive/simple/button/general/button.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <ui/interaction/iInteraction/empty/emptyInteraction.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, Button) {
	InitInfoData data{{100, 100}};
	
	ui::Button button{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IInteraction, ui::EmptyInteraction>(),
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &button);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(button.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(button.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(button.getSize(), sf::Vector2f{});
	ASSERT_EQ(button.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(button.getPosition(), sf::Vector2f{});
	ASSERT_EQ(button.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(button.updateInteractions({}), true);
	
	button.setSize({5, 11});
	ASSERT_EQ(button.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(button.getAreaSize(), (sf::Vector2f{5, 11}));
	
	button.setPosition({19, 39});
	ASSERT_EQ(button.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(button.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	button.resize({7, 13}, {23, 41});
	ASSERT_EQ(button.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(button.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(button.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(button.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	button.move({10, 5});
	ASSERT_EQ(button.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(button.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Button.png"));
}