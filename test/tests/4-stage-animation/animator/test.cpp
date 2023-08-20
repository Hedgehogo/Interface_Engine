#include <gtest/gtest.h>
#include "IE/animation/animator/Animator.hpp"
#include "../../../testsObjects/testAnimatorUnit/testAnimatorUnit.hpp"
TEST(Animator, update) {
	TestAnimatorUnit *test1_1 = new TestAnimatorUnit{},
					 *test1_2 = new TestAnimatorUnit{},
					 *test2_1 = new TestAnimatorUnit{},
					 *test3_1 = new TestAnimatorUnit{},
					 *test6and7_1 = new TestAnimatorUnit{},
					 *test1 = new TestAnimatorUnit{{test1_1, test1_2}},
					 *test2 = new TestAnimatorUnit{{test2_1}},
					 *test3 = new TestAnimatorUnit{{nullptr, test3_1}},
					 *test4 = new TestAnimatorUnit{{nullptr}},
					 *test5 = new TestAnimatorUnit{},
					 *test6 = new TestAnimatorUnit{{test6and7_1}},
					 *test7 = new TestAnimatorUnit{{test6and7_1}};

	ui::Animator animator{{test1, test2, test3, test4, test5, test6, test7}};

	animator.update(3.f);

	ASSERT_EQ(test1->getProcessed().update[0].timeParameter, 3.f);
	ASSERT_EQ(test2->getProcessed().update[0].timeParameter, 3.f);
	ASSERT_EQ(test4->getProcessed().update[0].timeParameter, 3.f);
	ASSERT_EQ(test3->getProcessed().update[0].timeParameter, 3.f);
	ASSERT_EQ(test5->getProcessed().update[0].timeParameter, 3.f);

	ASSERT_LT(test1->getProcessed().update[0].time, test2->getProcessed().update[0].time);
	ASSERT_LT(test2->getProcessed().update[0].time, test3->getProcessed().update[0].time);
	ASSERT_LT(test3->getProcessed().update[0].time, test4->getProcessed().update[0].time);
	ASSERT_LT(test4->getProcessed().update[0].time, test5->getProcessed().update[0].time);

	animator.update(4.f);

	ASSERT_EQ(test1_1->getProcessed().update[0].timeParameter, 4.f);
	ASSERT_EQ(test1_2->getProcessed().update[0].timeParameter, 4.f);
	ASSERT_EQ(test2_1->getProcessed().update[0].timeParameter, 4.f);
	ASSERT_EQ(test3_1->getProcessed().update[1].timeParameter, 4.f);
	ASSERT_EQ(test3->getProcessed().update[1].timeParameter, 4.f);
	ASSERT_EQ(test4->getProcessed().update[1].timeParameter, 4.f);

	ASSERT_EQ(test5->getProcessed().update.size(), 1);
	ASSERT_EQ(test6and7_1->getProcessed().update.size(), 1);

	ASSERT_LT(test1_1->getProcessed().update[0].time, test1_2->getProcessed().update[0].time);
	ASSERT_LT(test1_2->getProcessed().update[0].time, test2_1->getProcessed().update[0].time);
	ASSERT_LT(test2_1->getProcessed().update[0].time, test3->getProcessed().update[1].time);
	ASSERT_LT(test3->getProcessed().update[0].time, test3_1->getProcessed().update[1].time);
	ASSERT_LT(test3_1->getProcessed().update[0].time, test4->getProcessed().update[1].time);

	delete test1_1;
	delete test1_2;
	delete test2_1;
	delete test3_1;
}

TEST(Animator, copy) {
	TestAnimatorUnit *test1_1 = new TestAnimatorUnit{},
					 *test1_2 = new TestAnimatorUnit{},
					 *test2_1 = new TestAnimatorUnit{},
					 *test2_2 = new TestAnimatorUnit{},
					 *test1 = new TestAnimatorUnit{{test1_1, test1_2}},
					 *test2 = new TestAnimatorUnit{{test2_1, test2_2}};

	ui::Animator animator{{test1, test2}};

	delete animator.copy();

	ASSERT_EQ(test1->getProcessed().copy.size(), 1);
	ASSERT_EQ(test2->getProcessed().copy.size(), 1);
	ASSERT_EQ(test1_1->getProcessed().copy.size(), 1);
	ASSERT_EQ(test1_2->getProcessed().copy.size(), 1);
	ASSERT_EQ(test2_1->getProcessed().copy.size(), 1);
	ASSERT_EQ(test2_2->getProcessed().copy.size(), 1);

	animator.update(3.f);
	delete animator.copy();

	ASSERT_EQ(test1->getProcessed().copy.size(), 2);
	ASSERT_EQ(test2->getProcessed().copy.size(), 2);
	ASSERT_EQ(test1_1->getProcessed().copy.size(), 2);
	ASSERT_EQ(test1_2->getProcessed().copy.size(), 2);
	ASSERT_EQ(test2_1->getProcessed().copy.size(), 2);
	ASSERT_EQ(test2_2->getProcessed().copy.size(), 2);

	delete test1_1;
	delete test1_2;
	delete test2_1;
	delete test2_2;
}