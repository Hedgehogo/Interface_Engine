#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/BasicInteractiveData/BaseButton/Button/Button.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, Button) {
	InitInfoData data{{100, 100}};
	
	ie::Button button{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::makeBoxPtr<ie::IBaseInteraction, ie::EmptyInteraction>(),
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