#include <gtest/gtest.h>
#include "../test/testsObjects/testConvertToUse/testConvertToUse.hpp"
#include "IE/animation/variables/shared/sharedAnimationVariable.hpp"
#include "IE/../../test/testsObjects/testSValue/testSValue.hpp"

TEST(SharedAnimationVariable, valueFromAnimation) {
	TestConvertToUse *testConvertToUse{new TestConvertToUse{3}};
	std::shared_ptr<TestSValue> testSValue{new TestSValue{5}};
	ui::SharedAnimationVariable<float> sharedAnimationVariable{testSValue, testConvertToUse};

	sharedAnimationVariable.valueFromAnimation(2);

	ASSERT_EQ(testSValue->getProcessed().setValue[0].value, 3);
}
