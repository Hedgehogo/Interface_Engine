#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/BasicInteractiveData/BaseSlider/ConstSlider/ConstSlider.hpp>
#include <IE/component/IComponent/IScalable/IUninteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include "_test/_image_equal/image_equal.hpp"

TEST(IComponent, ConstSlider) {
	InitInfoData data{{100, 100}};
	
	auto value = std::make_shared<ie::SRVec2f>(sf::Vector2f{0.f, 0.f});
	ie::ConstSlider const_slider{
		{
			ie::make_box_ptr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::IUninteractive::Make, ie::FullColor::Make>(sf::Color::Red),
			value
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 2);
	ASSERT_EQ(data.update_manager.size(), 1);
	ASSERT_EQ(&data.update_manager.get(0), &const_slider);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(const_slider.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(const_slider.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(const_slider.get_size(), sf::Vector2f{});
	ASSERT_EQ(const_slider.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(const_slider.get_position(), sf::Vector2f{});
	ASSERT_EQ(const_slider.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(const_slider.update_interactions({}), true);
	
	const_slider.set_size({5, 11});
	ASSERT_EQ(const_slider.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(const_slider.get_area_size(), (sf::Vector2f{5, 11}));
	
	const_slider.set_position({19, 39});
	ASSERT_EQ(const_slider.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(const_slider.get_area_position(), (sf::Vector2f{19, 39}));
	
	const_slider.resize({7, 13}, {23, 41});
	ASSERT_EQ(const_slider.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(const_slider.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(const_slider.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(const_slider.get_area_position(), (sf::Vector2f{23, 41}));
	
	const_slider.move({10, 5});
	ASSERT_EQ(const_slider.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(const_slider.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/ConstSlider-0.0.png"));
	
	value->set_value(sf::Vector2f{0.0f, 0.7f});
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/ConstSlider-0.7.png"));
	
	value->set_value(sf::Vector2f{0.0f, 1.0f});
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/ConstSlider-1.0.png"));
}