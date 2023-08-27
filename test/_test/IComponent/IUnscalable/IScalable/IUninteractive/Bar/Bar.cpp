#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/Bar/Bar.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>

TEST(IComponent, Bar) {
	InitInfoData data{{100, 100}};
	
	ie::Bar bar{
		{
			ie::makeBoxPtr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Yellow),
			ie::makeBoxPtr<ie::IUninteractive::Make, ie::Capsule::Make>(sf::Color::Red),
			0.2f
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 3);
	ASSERT_EQ(&data.drawManager.get(0), &bar);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(&bar.getRenderTarget(), &data.renderTarget);
	ASSERT_EQ(bar.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(bar.getNormalSize(), (sf::Vector2f{0, 1}));
	ASSERT_EQ(bar.getSize(), sf::Vector2f{});
	ASSERT_EQ(bar.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(bar.getPosition(), sf::Vector2f{});
	ASSERT_EQ(bar.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(bar.updateInteractions({}), true);
	
	bar.setSize({5, 11});
	ASSERT_EQ(bar.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(bar.getAreaSize(), (sf::Vector2f{5, 11}));
	
	bar.setPosition({19, 39});
	ASSERT_EQ(bar.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(bar.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	bar.resize({23, 41}, {7, 13});
	ASSERT_EQ(bar.getSize(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(bar.getAreaSize(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(bar.getPosition(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(bar.getAreaPosition(), (sf::Vector2f{7, 13}));
	
	bar.move({10, 5});
	ASSERT_EQ(bar.getPosition(), (sf::Vector2f{17, 18}));
	ASSERT_EQ(bar.getAreaPosition(), (sf::Vector2f{17, 18}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Bar.png"));
}