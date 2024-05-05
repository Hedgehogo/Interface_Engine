#include <gtest/gtest.h>
#include <IE/component/IComponent/IScalable/Box/BoxAlternative/BoxAlternative.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/FullColor/FullColor.hpp>
#include <IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <IComponent/_InitInfoData/InitInfoData.hpp>
#include "_image_equal/image_equal.hpp"

TEST(IComponent, BoxAlternative) {
	InitInfoData data{{100, 100}};
	
	ie::BoxAlternative box_alternative{
		{
			ie::make_box_ptr<ie::IScalable::Make, ie::Capsule::Make>(sf::Color::Green),
			ie::make_box_ptr<ie::IScalable::Make, ie::FullColor::Make>(sf::Color::Red)
		},
		data.make_init_info()
	};
	data.interaction_manager.update({});
	
	ASSERT_EQ(data.draw_manager.size(), 2);
	ASSERT_EQ(data.update_manager.size(), 0);
	ASSERT_EQ(data.interaction_manager.size(), 0);
	ASSERT_EQ(data.panel_manager.size(), 0);
	
	ASSERT_EQ(box_alternative.get_min_size(), sf::Vector2f{});
	ASSERT_EQ(box_alternative.get_normal_size(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(box_alternative.get_size(), sf::Vector2f{});
	ASSERT_EQ(box_alternative.get_area_size(), sf::Vector2f{});
	ASSERT_EQ(box_alternative.get_position(), sf::Vector2f{});
	ASSERT_EQ(box_alternative.get_area_position(), sf::Vector2f{});
	ASSERT_EQ(box_alternative.handle_event(ie::Event::Pointer({std::numeric_limits<size_t>::max(), {}})), true);
	
	box_alternative.set_size({5, 11});
	ASSERT_EQ(box_alternative.get_size(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(box_alternative.get_area_size(), (sf::Vector2f{5, 11}));
	
	box_alternative.set_position({19, 39});
	ASSERT_EQ(box_alternative.get_position(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(box_alternative.get_area_position(), (sf::Vector2f{19, 39}));
	
	box_alternative.resize({7, 13}, {23, 41});
	ASSERT_EQ(box_alternative.get_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_alternative.get_area_size(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(box_alternative.get_position(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(box_alternative.get_area_position(), (sf::Vector2f{23, 41}));
	
	box_alternative.move({10, 5});
	ASSERT_EQ(box_alternative.get_position(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(box_alternative.get_area_position(), (sf::Vector2f{33, 46}));
	
	data.draw_manager.draw();
	ASSERT_TRUE(data.render_equal_with_save("test-src/BoxAlternative.png"));
}