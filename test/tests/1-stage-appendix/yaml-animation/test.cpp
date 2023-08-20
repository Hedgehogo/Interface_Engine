#include <gtest/gtest.h>
#include "modules/appendix/yaml-Animation/buffer.hpp"
#include "../../../testsObjects/testAnimatorUnit/testAnimatorUnit.hpp"
#include "../../../testsObjects/testAnimationVariable/testAnimationVariable.hpp"

TEST(yamlAnimationBuffer, animatorUnitRequestUpdate) {
	TestAnimatorUnit *testBuffer1 = new TestAnimatorUnit{},
					 *testBuffer2 = new TestAnimatorUnit{},
					 *testRequest1 = new TestAnimatorUnit{},
					 *testRequest2 = new TestAnimatorUnit{},
					 *testRequest3 = new TestAnimatorUnit{},
					 *testRequest4 = new TestAnimatorUnit{};
	ui::animatorUnitBuffer = {
		{"a", testBuffer1},
		{"b", testBuffer2}
	};

	ui::animatorUnitRequest = {
		{"a", {[&](ui::IAnimatorUnit *unit){testRequest1->addNextUnits(unit);}, [&](ui::IAnimatorUnit *unit){testRequest2->addNextUnits(unit);}}},
		{"b", {[&](ui::IAnimatorUnit *unit){testRequest3->addNextUnits(unit);}, [&](ui::IAnimatorUnit *unit){testRequest4->addNextUnits(unit);}}}
	};

	ui::animatorUnitRequestUpdate();

	ASSERT_EQ(testRequest1->getProcessed().addNextUnits[0].nextUnit, testBuffer1);
	ASSERT_EQ(testRequest2->getProcessed().addNextUnits[0].nextUnit, testBuffer1);
	ASSERT_EQ(testRequest3->getProcessed().addNextUnits[0].nextUnit, testBuffer2);
	ASSERT_EQ(testRequest4->getProcessed().addNextUnits[0].nextUnit, testBuffer2);

	ui::animationVariablesBuffer = {};
	ui::animatorUnitRequest = {};
}
