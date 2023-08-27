#include <gtest/gtest.h>
#include "IE/Animation/variables/base/animationVariable.hpp"
#include "IE/../../test/testsObjects/testConvertToUse/testConvertToUse.hpp"

TEST(AnimationVariable, get_set) {
	TestConvertToUse *testConvertToUse{new TestConvertToUse{5}};
	ie::AnimationVariable animationVariable{0.5f, testConvertToUse};

	ASSERT_EQ(animationVariable.get(), 0.5);

	animationVariable.set(3);
	ASSERT_EQ(animationVariable.get(), 3);

	animationVariable = 5;
	ASSERT_EQ(animationVariable.get(), 5);
}

TEST(AnimationVariable, addAnimationSetter_valueFromAnimation) {
	TestConvertToUse *testConvertToUse1{new TestConvertToUse{3}};
	ie::AnimationVariable animationVariable1{0.5f, testConvertToUse1};

	animationVariable1.addAnimationSetter([&](float value){
		ASSERT_EQ(value, 3);
	});

	animationVariable1.valueFromAnimation(2);
	ASSERT_EQ(testConvertToUse1->getProcessed().convert[0].value, 2);
	ASSERT_EQ(animationVariable1.get(), 3);


	TestConvertToUse *testConvertToUse2{new TestConvertToUse{5}};
	ie::AnimationVariable animationVariable2{0.5f, testConvertToUse2, false};

	animationVariable2.addAnimationSetter([&](float value){
		ASSERT_EQ(value, 5);
	});

	animationVariable2.valueFromAnimation(4);
	ASSERT_EQ(testConvertToUse2->getProcessed().convert[0].value, 4);
	ASSERT_EQ(animationVariable2.get(), 0.5);

}
