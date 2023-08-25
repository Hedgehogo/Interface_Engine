#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/IInteractive/BasicBaseInteractive/BaseSlider/Slider/Slider.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, Slider) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ui::SRVec2f>(sf::Vector2f{0.f, 0.f});
	ui::Slider slider{
		{
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Green),
			ui::makeBoxPtr<ui::IUninteractive::Make, ui::FullColor::Make>(sf::Color::Red),
			value
		}, data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 2);
	ASSERT_EQ(data.updateManager.size(), 1);
	ASSERT_EQ(&data.updateManager.get(0), &slider);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(slider.getMinSize(), sf::Vector2f{});
	ASSERT_EQ(slider.getNormalSize(), sf::Vector2f{});
	ASSERT_EQ(slider.getSize(), sf::Vector2f{});
	ASSERT_EQ(slider.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(slider.getPosition(), sf::Vector2f{});
	ASSERT_EQ(slider.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(slider.updateInteractions({}), true);
	
	slider.setSize({5, 11});
	ASSERT_EQ(slider.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(slider.getAreaSize(), (sf::Vector2f{5, 11}));
	
	slider.setPosition({19, 39});
	ASSERT_EQ(slider.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(slider.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	slider.resize({7, 13}, {23, 41});
	ASSERT_EQ(slider.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(slider.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(slider.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(slider.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	slider.move({10, 5});
	ASSERT_EQ(slider.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(slider.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Slider-0.0.png"));
	
	value->setValue(sf::Vector2f{0.0f, 0.7f});
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Slider-0.7.png"));
	
	value->setValue(sf::Vector2f{0.0f, 1.0f});
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/Slider-1.0.png"));
}