#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/IInteractive/BaseInteractive/Switcher/Switcher.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, Switcher) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ui::Sbool>(false);
	ui::Switcher switcher{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
			value
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &switcher);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &switcher);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(switcher.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(switcher.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(switcher.getSize(), sf::Vector2f{});
	ASSERT_EQ(switcher.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(switcher.getPosition(), sf::Vector2f{});
	ASSERT_EQ(switcher.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(switcher.updateInteractions({}), true);
	
	switcher.setSize({5, 11});
	ASSERT_EQ(switcher.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(switcher.getAreaSize(), (sf::Vector2f{5, 11}));
	
	switcher.setPosition({19, 39});
	ASSERT_EQ(switcher.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(switcher.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	switcher.resize({7, 13}, {23, 41});
	ASSERT_EQ(switcher.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(switcher.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(switcher.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(switcher.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	switcher.move({10, 5});
	ASSERT_EQ(switcher.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(switcher.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Switcher-false.png"));
	
	value->setValue(true);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Switcher-true.png"));
}