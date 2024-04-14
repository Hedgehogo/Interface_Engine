#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/BasicInteractiveData/BaseSlider/Slider/Slider.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp>
#include <IE/shared/ISReadable/ISVec2/SVec2/SVec2.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include <_image_equal/image_equal.hpp>

TEST(IComponent, Slider) {
	InitInfoData data{{100, 100}};
	
	ie::SMRFloat value_x{0};
	ie::SMRFloat value_y{0};
	ie::SMRVec2F value{value_x, value_y};
	ie::Slider slider{
		{
			ie::make_box_ptr<ie::INonInteractive::Make, ie::FullColor::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::INonInteractive::Make, ie::FullColor::Make>(sf::Color::Red),
			value
		}, data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 2);
	ASSERT_EQ(data.update_manager.size(), 1);
	ASSERT_EQ(&data.update_manager.get(0), &slider);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(slider.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(slider.get_normal_size(), sf::Vector2f{});
	ASSERT_EQ(slider.get_size(), sf::Vector2f{});
	ASSERT_EQ(slider.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(slider.get_position(), sf::Vector2f{});
	ASSERT_EQ(slider.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(slider.handle_event(ie::Event::Touch(std::numeric_limits<size_t>::max(), {})), true);
	
	slider.set_size({5, 11});
	ASSERT_EQ(slider.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(slider.get_area_size(), (sf::Vector2f{5, 11}));
	
	slider.set_position({19, 39});
	ASSERT_EQ(slider.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(slider.get_area_position(), (sf::Vector2f{19, 39}));
	
	slider.resize({7, 14}, {23, 41});
	ASSERT_EQ(slider.get_size(), (sf::Vector2f{7, 14}));
	ASSERT_EQ(slider.get_area_size(), (sf::Vector2f{7, 14}));
	ASSERT_EQ(slider.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(slider.get_area_position(), (sf::Vector2f{23, 41}));
	
	slider.move({10, 5});
	ASSERT_EQ(slider.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(slider.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Slider-0.0.png"));
	
	value.set(sf::Vector2f{0.0f, 0.7f});
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Slider-0.7.png"));
	
	value.set(sf::Vector2f{0.0f, 1.0f});
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/Slider-1.0.png"));
}