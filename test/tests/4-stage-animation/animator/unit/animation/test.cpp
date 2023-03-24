#include <gtest/gtest.h>
#include "ui/animation/animator/unit/animation/animation.hpp"
#include "../test/testsObjects/testAnimationVariable/testAnimationVariable.hpp"
#include "../test/testsObjects/testChangeVariable/testChangeVariable.hpp"
#include "../test/testsObjects/testAnimatorUnit/testAnimatorUnit.hpp"

TEST(Animation, update) {
	auto *testChangeVariable1a = new TestChangeVariable{1, 2},
					   *testChangeVariable1b = new TestChangeVariable{1, 2},
					   *testChangeVariable2a = new TestChangeVariable{1, 2},
					   *testChangeVariable2b = new TestChangeVariable{1, 2};
	auto *testAnimationVariable1 = new TestAnimationVariable{},
						  *testAnimationVariable2 = new TestAnimationVariable{};
	auto *testAnimatorUnit = new TestAnimatorUnit{};
	ui::Animation animation{
		{
			{
				testAnimationVariable1,
				{testChangeVariable1a, testChangeVariable1b}
			},
			{
				testAnimationVariable2,
				{testChangeVariable2a, testChangeVariable2b}
			}
		},
		{testAnimatorUnit, nullptr}
	};

	auto nextAnim = animation.update(0.1);

	ASSERT_EQ(nextAnim.size(), 1);
	ASSERT_EQ(nextAnim[0], &animation);

	ASSERT_EQ(testChangeVariable1a->getProcessed().operat[0].frame, 0);
	ASSERT_EQ(testChangeVariable2a->getProcessed().operat[0].frame, 0);

	ASSERT_EQ(testChangeVariable1b->getProcessed().operat.size(), 0);
	ASSERT_EQ(testChangeVariable2b->getProcessed().operat.size(), 0);

	nextAnim = animation.update(0.5);

	ASSERT_EQ(nextAnim.size(), 1);
	ASSERT_EQ(nextAnim[0], &animation);

	ASSERT_EQ(testChangeVariable1a->getProcessed().operat[1].frame, 0.4f);
	ASSERT_EQ(testChangeVariable2a->getProcessed().operat[1].frame, 0.4f);

	ASSERT_EQ(testChangeVariable1b->getProcessed().operat.size(), 0);
	ASSERT_EQ(testChangeVariable2b->getProcessed().operat.size(), 0);

	nextAnim = animation.update(1.5);

	ASSERT_EQ(nextAnim.size(), 1);
	ASSERT_EQ(nextAnim[0], &animation);

	ASSERT_EQ(testChangeVariable1a->getProcessed().operat.size(), 2);
	ASSERT_EQ(testChangeVariable2a->getProcessed().operat.size(), 2);


	ASSERT_EQ(testChangeVariable1b->getProcessed().operat[0].frame, 1.4f);
	ASSERT_EQ(testChangeVariable2b->getProcessed().operat[0].frame, 1.4f);

	nextAnim = animation.update(3);

	ASSERT_EQ(nextAnim.size(), 2);
	ASSERT_EQ(nextAnim[0], testAnimatorUnit);
	ASSERT_EQ(nextAnim[1], &animation);
}

TEST(Animation, restart) {
	auto *testChangeVariable = new TestChangeVariable{1, 2};
	auto *testAnimationVariable = new TestAnimationVariable{};
	ui::Animation animation{
		{
			{
				testAnimationVariable,
				{
					testChangeVariable
				}
			}
		}
	};

	animation.update(0.1);

	ASSERT_EQ(testChangeVariable->getProcessed().operat[0].frame, 0);

	animation.update(1.1);

	ASSERT_EQ(testChangeVariable->getProcessed().operat[1].frame, 1);

	animation.restart();
	animation.update(0.1);

	ASSERT_EQ(testChangeVariable->getProcessed().operat[2].frame, 0);
}

TEST(Animation, setNextUnits) {
	auto *testChangeVariable = new TestChangeVariable{1, 2};
	auto *testAnimationVariable = new TestAnimationVariable{};
	auto *testAnimatorUnit1 = new TestAnimatorUnit{},
					 *testAnimatorUnit2 = new TestAnimatorUnit{},
					 *testAnimatorUnit3 = new TestAnimatorUnit{};
	ui::Animation animation{
		{
			{
				testAnimationVariable,
				{
					testChangeVariable
				}
			}
		},
		{testAnimatorUnit1}
	};

	animation.update(0.1);
	auto next = animation.update(2);
	ASSERT_EQ(next.size(), 1);
	ASSERT_EQ(next[0], testAnimatorUnit1);
	animation.restart();

	animation.setNextUnits({testAnimatorUnit2, testAnimatorUnit3});
	animation.update(0.1);
	next = animation.update(2);
	ASSERT_EQ(next.size(), 2);
	ASSERT_EQ(next[0], testAnimatorUnit2);
	ASSERT_EQ(next[1], testAnimatorUnit3);

	delete testAnimatorUnit2;
	delete testAnimatorUnit3;
}

TEST(Animation, addNextUnits) {
	auto *testChangeVariable = new TestChangeVariable{1, 2};
	auto *testAnimationVariable = new TestAnimationVariable{};
	auto *testAnimatorUnit1 = new TestAnimatorUnit{},
					 *testAnimatorUnit2 = new TestAnimatorUnit{};
	ui::Animation animation{
		{
			{
				testAnimationVariable,
				{
					testChangeVariable
				}
			}
		},
		{testAnimatorUnit1}
	};

	animation.update(0.1);
	auto next = animation.update(2);
	ASSERT_EQ(next.size(), 1);
	ASSERT_EQ(next[0], testAnimatorUnit1);
	animation.restart();

	animation.addNextUnits(testAnimatorUnit2);
	animation.update(0.1);
	next = animation.update(2);
	ASSERT_EQ(next.size(), 2);
	ASSERT_EQ(next[0], testAnimatorUnit1);
	ASSERT_EQ(next[1], testAnimatorUnit2);

	delete testAnimatorUnit2;
}

TEST(Animation, copy) {
	auto *testChangeVariable = new TestChangeVariable{1, 2};
	auto *testAnimationVariable = new TestAnimationVariable{};
	auto *testAnimatorUnit1 = new TestAnimatorUnit{},
		 *testAnimatorUnit2 = new TestAnimatorUnit{},
		 *testAnimatorUnit3 = new TestAnimatorUnit{},
		 *testAnimatorUnit4 = new TestAnimatorUnit{},
		 *testAnimatorUnit5 = new TestAnimatorUnit{};
	ui::Animation animation1{
		{
			{
				testAnimationVariable,
				{
					testChangeVariable
				}
			}
		},
		{testAnimatorUnit1}
	};
	animation1.setNextUnits({testAnimatorUnit2, testAnimatorUnit3});

	delete animation1.copy();

	ASSERT_EQ(testChangeVariable->getProcessed().copy.size(), 1);
	ASSERT_EQ(testAnimatorUnit1->getProcessed().copy.size(), 1);
	ASSERT_EQ(testAnimatorUnit2->getProcessed().copy.size(), 0);
	ASSERT_EQ(testAnimatorUnit3->getProcessed().copy.size(), 0);

	ui::Animation animation2{
		{
			{
				testAnimationVariable,
				{
					testChangeVariable
				}
			}
		},
		{testAnimatorUnit4}
	};
	animation2.addNextUnits(testAnimatorUnit5);

	delete animation2.copy();

	ASSERT_EQ(testAnimatorUnit4->getProcessed().copy.size(), 1);
	ASSERT_EQ(testAnimatorUnit5->getProcessed().copy.size(), 0);

	delete testAnimatorUnit2;
	delete testAnimatorUnit3;
	delete testAnimatorUnit5;
}
