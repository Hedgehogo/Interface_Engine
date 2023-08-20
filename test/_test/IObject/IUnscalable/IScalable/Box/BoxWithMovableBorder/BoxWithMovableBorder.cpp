#include <gtest/gtest.h>
#include <IE/iObject/iUnscalable/iScalable/box/movableBorder/boxWithMovableBorder.hpp>
#include <IE/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithMovableBorder) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ui::SCoefficient>(0.f);
	ui::BoxWithMovableBorder boxWithMovableBorder{
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
	ASSERT_EQ(&data.updateManager.get(0), &boxWithMovableBorder);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithMovableBorder.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithMovableBorder.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithMovableBorder.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithMovableBorder.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithMovableBorder.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithMovableBorder.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithMovableBorder.updateInteractions({}), true);
	
	boxWithMovableBorder.setSize({5, 11});
	ASSERT_EQ(boxWithMovableBorder.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithMovableBorder.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithMovableBorder.setPosition({19, 39});
	ASSERT_EQ(boxWithMovableBorder.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithMovableBorder.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithMovableBorder.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithMovableBorder.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithMovableBorder.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithMovableBorder.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithMovableBorder.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithMovableBorder.move({10, 5});
	ASSERT_EQ(boxWithMovableBorder.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithMovableBorder.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithMovableBorder-0.0.png"));
	
	value->setValue(0.7f);
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithMovableBorder-0.7.png"));
}