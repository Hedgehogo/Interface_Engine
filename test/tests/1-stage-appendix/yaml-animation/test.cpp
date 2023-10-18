#include <gtest/gtest.h>
#include "IE/Modules/yaml-Animation/Buffer.hpp"
#include "../../../tests_objects/test_animator_unit/test_animator_unit.hpp"
#include "../../../tests_objects/test_animation_variable/test_animation_variable.hpp"

TEST(yaml_animation_buffer, animator_unit_request_update) {
	TestAnimatorUnit *test_buffer1 = new TestAnimatorUnit{},
					 *test_buffer2 = new TestAnimatorUnit{},
					 *test_request1 = new TestAnimatorUnit{},
					 *test_request2 = new TestAnimatorUnit{},
					 *test_request3 = new TestAnimatorUnit{},
					 *test_request4 = new TestAnimatorUnit{};
	ie::animator_unit_buffer = {
		{"a", test_buffer1},
		{"b", test_buffer2}
	};

	ie::animator_unit_request = {
		{"a", {[&](ie::IAnimatorUnit *unit){test_request1->add_next_units(unit);}, [&](ie::IAnimatorUnit *unit){test_request2->add_next_units(unit);}}},
		{"b", {[&](ie::IAnimatorUnit *unit){test_request3->add_next_units(unit);}, [&](ie::IAnimatorUnit *unit){test_request4->add_next_units(unit);}}}
	};

	ie::animator_unit_request_update();

	ASSERT_EQ(test_request1->get_processed().add_next_units[0].next_unit, test_buffer1);
	ASSERT_EQ(test_request2->get_processed().add_next_units[0].next_unit, test_buffer1);
	ASSERT_EQ(test_request3->get_processed().add_next_units[0].next_unit, test_buffer2);
	ASSERT_EQ(test_request4->get_processed().add_next_units[0].next_unit, test_buffer2);

	ie::animation_variables_buffer = {};
	ie::animator_unit_request = {};
}
