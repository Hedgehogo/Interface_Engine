#include <gtest/gtest.h>
#include "IE/Animation/variables/base/animation_variable.hpp"
#include "IE/../../test/tests_objects/test_convert_to_use/test_convert_to_use.hpp"

TEST(AnimationVariable, get_set) {
	TestConvertToUse *test_convert_to_use{new TestConvertToUse{5}};
	ie::AnimationVariable animation_variable{0.5f, test_convert_to_use};

	ASSERT_EQ(animation_variable.get(), 0.5);

	animation_variable.set(3);
	ASSERT_EQ(animation_variable.get(), 3);

	animation_variable = 5;
	ASSERT_EQ(animation_variable.get(), 5);
}

TEST(AnimationVariable, add_animation_setter_value_from_animation) {
	TestConvertToUse *test_convert_to_use1{new TestConvertToUse{3}};
	ie::AnimationVariable animation_variable1{0.5f, test_convert_to_use1};

	animation_variable1.add_animation_setter([&](float value){
		ASSERT_EQ(value, 3);
	});

	animation_variable1.value_from_animation(2);
	ASSERT_EQ(test_convert_to_use1->get_processed().convert[0].value, 2);
	ASSERT_EQ(animation_variable1.get(), 3);


	TestConvertToUse *test_convert_to_use2{new TestConvertToUse{5}};
	ie::AnimationVariable animation_variable2{0.5f, test_convert_to_use2, false};

	animation_variable2.add_animation_setter([&](float value){
		ASSERT_EQ(value, 5);
	});

	animation_variable2.value_from_animation(4);
	ASSERT_EQ(test_convert_to_use2->get_processed().convert[0].value, 4);
	ASSERT_EQ(animation_variable2.get(), 0.5);

}
