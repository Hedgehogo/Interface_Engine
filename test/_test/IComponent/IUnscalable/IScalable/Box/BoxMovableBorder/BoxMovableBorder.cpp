#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxMovableBorder/BoxMovableBorder.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, BoxMovableBorder) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ui::SCoefficient>(0.f);
	ui::BoxMovableBorder boxMovableBorder{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IScalable::Make, ui::FullColor::Make>(sf::Color::Red),
			false,
			value
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &boxMovableBorder);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxMovableBorder.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxMovableBorder.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxMovableBorder.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxMovableBorder.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxMovableBorder.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxMovableBorder.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxMovableBorder.updateInteractions({}), true);
	
	boxMovableBorder.setSize({5, 11});
	ASSERT_EQ(boxMovableBorder.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxMovableBorder.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxMovableBorder.setPosition({19, 39});
	ASSERT_EQ(boxMovableBorder.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxMovableBorder.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxMovableBorder.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxMovableBorder.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxMovableBorder.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxMovableBorder.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxMovableBorder.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxMovableBorder.move({10, 5});
	ASSERT_EQ(boxMovableBorder.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxMovableBorder.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxMovableBorder-0.0.png"));
	
	value->setValue(0.7f);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxMovableBorder-0.7.png"));
}