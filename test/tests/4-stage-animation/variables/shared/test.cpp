#include <gtest/gtest.h>
#include "../test/tests_objects/test_convert_to_use/test_convert_to_use.hpp"
#include "IE/Animation/variables/shared/shared_animation_variable.hpp"
#include "IE/../../test/tests_objects/test_s_value/test_s_value.hpp"

TEST(SharedAnimationVariable, value_from_animation) {
	TestConvertToUse *test_convert_to_use{new TestConvertToUse{3}};
	std::shared_ptr<TestSValue> test_s_value{new TestSValue{5}};
	ie::SharedAnimationVariable<float> shared_animation_variable{test_s_value, test_convert_to_use};

	shared_animation_variable.value_from_animation(2);

	ASSERT_EQ(test_s_value->get_processed().set_value[0].value, 3);
}
