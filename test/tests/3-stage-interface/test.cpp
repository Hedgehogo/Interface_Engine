#include "../../create_test_program/create_test_program.hpp"
#include "../../tests_objects/test_object/test_object.hpp"
#include "../../tests_objects/test_panel/test_panel.hpp"

TEST(Interface, draw) {
	auto test_object = new TestObject{};
	auto test_panel = new TestPanel{};
	auto test_interface = new ie::Interface{test_object};


	test_interface->get_panel_manager()->display_panel(test_panel);

    Program test_program{
		test_interface,
        {1, 1}
    };

	ASSERT_GT(test_object->get_processed().draw, 0);

	ASSERT_GT(test_panel->get_processed().draw, 0);

	ASSERT_GT(test_panel->get_processed().draw, test_object->get_processed().draw);
}

TEST(Interface, init) {
	auto test_object = new TestObject;
	auto test_panel = new TestPanel{};
	auto test_interface = new ie::Interface{test_object};


	test_interface->get_panel_manager()->display_panel(test_panel);

	Program test_program{
		test_interface,
		{1, 1}
	};

	ASSERT_GT(test_object->get_processed().init.time, 0);

	ASSERT_EQ(test_interface->get_render_target(), test_object->get_processed().init.render_target);
	ASSERT_EQ(test_interface->get_draw_manager(), test_object->get_processed().init.draw_manager);
	ASSERT_EQ(test_interface->get_update_manager(), test_object->get_processed().init.update_manager);
	ASSERT_EQ(test_interface->get_interaction_stack(), test_object->get_processed().init.interaction_stack);
	ASSERT_EQ(test_interface->get_interaction_manager(), test_object->get_processed().init.interaction_manager);
	ASSERT_EQ(test_interface->get_panel_manager(), test_object->get_processed().init.panel_manager);
}

TEST(Interface, resize) {
    auto full_color = new ie::FullColor{sf::Color::Red};
    ie::Interface interface{full_color};
    interface.resize({10, 10}, {5, 5});

    ASSERT_TRUE((full_color->get_size() == sf::Vector2f{10, 10}));
    ASSERT_TRUE((full_color->get_position() == sf::Vector2f{5, 5}));
}

TEST(Interface, set_size) {
    auto full_color = new ie::FullColor{sf::Color::Red};
    ie::Interface interface{full_color};
    interface.set_size({10, 10});

    ASSERT_TRUE((full_color->get_size() == sf::Vector2f{10, 10}));
	ASSERT_TRUE((interface.get_size() == sf::Vector2f{10, 10}));
}

TEST(Interface, set_position) {
    auto full_color = new ie::FullColor{sf::Color::Red};
    ie::Interface interface{full_color};
    interface.set_position({5, 5});

    ASSERT_TRUE((full_color->get_position() == sf::Vector2f{5, 5}));
	ASSERT_TRUE((interface.get_position() == sf::Vector2f{5, 5}));
}

TEST(Interface, move) {
	auto full_color = new ie::FullColor{sf::Color::Red};
	ie::Interface interface{full_color};
	interface.set_position({5, 5});

	ASSERT_TRUE((full_color->get_position() == sf::Vector2f{5, 5}));
	ASSERT_TRUE((interface.get_position() == sf::Vector2f{5, 5}));
}


TEST(Interface, min_size) {
	ie::Interface interface{new TestObject{{10, 10}}};
	ASSERT_TRUE((interface.get_min_size() == sf::Vector2f{ 10, 10 }));
}

TEST(Interface, normal_size) {
	ie::Interface interface{new TestObject{{10, 10}, {20, 20}}};
	ASSERT_TRUE((interface.get_normal_size() == sf::Vector2f{20, 20}));
}

TEST(Interface, copy) {
	auto test_object = new TestObject;

	Program test_program{
		new ie::Interface{
			test_object
		},
		{1, 1}
	};

	ie::Interface interface_copy = *test_program.interface->copy();

	ASSERT_GT(test_object->get_processed().copy, 0);

	ASSERT_EQ(interface_copy.get_normal_size(), test_program.interface->get_normal_size());
	ASSERT_EQ(interface_copy.get_area_position(), test_program.interface->get_area_position());
	ASSERT_EQ(interface_copy.get_area_size(), test_program.interface->get_area_size());
	ASSERT_EQ(interface_copy.get_min_size(), test_program.interface->get_min_size());
	ASSERT_EQ(interface_copy.get_position(), test_program.interface->get_position());
	ASSERT_EQ(interface_copy.get_size(), test_program.interface->get_size());
	ASSERT_EQ(interface_copy.get_render_target(), test_program.interface->get_render_target());
	ASSERT_EQ(interface_copy.get_interaction_stack(), test_program.interface->get_interaction_stack());
}
