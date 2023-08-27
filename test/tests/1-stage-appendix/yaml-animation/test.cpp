#include <gtest/gtest.h>
#include "IE/Modules/yaml-Animation/buffer.hpp"
#include "../../../testsObjects/testAnimatorUnit/testAnimatorUnit.hpp"
#include "../../../testsObjects/testAnimationVariable/testAnimationVariable.hpp"

TEST(yamlAnimationBuffer, animatorUnitRequestUpdate) {
	TestAnimatorUnit *testBuffer1 = new TestAnimatorUnit{},
					 *testBuffer2 = new TestAnimatorUnit{},
					 *testRequest1 = new TestAnimatorUnit{},
					 *testRequest2 = new TestAnimatorUnit{},
					 *testRequest3 = new TestAnimatorUnit{},
					 *testRequest4 = new TestAnimatorUnit{};
	ie::animatorUnitBuffer = {
		{"a", testBuffer1},
		{"b", testBuffer2}
	};

	ie::animatorUnitRequest = {
		{"a", {[&](ie::IAnimatorUnit *unit){testRequest1->addNextUnits(unit);}, [&](ie::IAnimatorUnit *unit){testRequest2->addNextUnits(unit);}}},
		{"b", {[&](ie::IAnimatorUnit *unit){testRequest3->addNextUnits(unit);}, [&](ie::IAnimatorUnit *unit){testRequest4->addNextUnits(unit);}}}
	};

	ie::animatorUnitRequestUpdate();

	ASSERT_EQ(testRequest1->getProcessed().addNextUnits[0].nextUnit, testBuffer1);
	ASSERT_EQ(testRequest2->getProcessed().addNextUnits[0].nextUnit, testBuffer1);
	ASSERT_EQ(testRequest3->getProcessed().addNextUnits[0].nextUnit, testBuffer2);
	ASSERT_EQ(testRequest4->getProcessed().addNextUnits[0].nextUnit, testBuffer2);

	ie::animationVariablesBuffer = {};
	ie::animatorUnitRequest = {};
}
