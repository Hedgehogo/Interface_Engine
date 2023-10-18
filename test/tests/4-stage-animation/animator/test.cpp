#include <gtest/gtest.h>
#include "IE/Animation/Animator/Animator.hpp"
#include "../../../tests_objects/test_animator_unit/test_animator_unit.hpp"
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

	ie::Animator animator{{test1, test2, test3, test4, test5, test6, test7}};

	animator.update(3.f);

	ASSERT_EQ(test1->get_processed().update[0].time_parameter, 3.f);
	ASSERT_EQ(test2->get_processed().update[0].time_parameter, 3.f);
	ASSERT_EQ(test4->get_processed().update[0].time_parameter, 3.f);
	ASSERT_EQ(test3->get_processed().update[0].time_parameter, 3.f);
	ASSERT_EQ(test5->get_processed().update[0].time_parameter, 3.f);

	ASSERT_LT(test1->get_processed().update[0].time, test2->get_processed().update[0].time);
	ASSERT_LT(test2->get_processed().update[0].time, test3->get_processed().update[0].time);
	ASSERT_LT(test3->get_processed().update[0].time, test4->get_processed().update[0].time);
	ASSERT_LT(test4->get_processed().update[0].time, test5->get_processed().update[0].time);

	animator.update(4.f);

	ASSERT_EQ(test1_1->get_processed().update[0].time_parameter, 4.f);
	ASSERT_EQ(test1_2->get_processed().update[0].time_parameter, 4.f);
	ASSERT_EQ(test2_1->get_processed().update[0].time_parameter, 4.f);
	ASSERT_EQ(test3_1->get_processed().update[1].time_parameter, 4.f);
	ASSERT_EQ(test3->get_processed().update[1].time_parameter, 4.f);
	ASSERT_EQ(test4->get_processed().update[1].time_parameter, 4.f);

	ASSERT_EQ(test5->get_processed().update.size(), 1);
	ASSERT_EQ(test6and7_1->get_processed().update.size(), 1);

	ASSERT_LT(test1_1->get_processed().update[0].time, test1_2->get_processed().update[0].time);
	ASSERT_LT(test1_2->get_processed().update[0].time, test2_1->get_processed().update[0].time);
	ASSERT_LT(test2_1->get_processed().update[0].time, test3->get_processed().update[1].time);
	ASSERT_LT(test3->get_processed().update[0].time, test3_1->get_processed().update[1].time);
	ASSERT_LT(test3_1->get_processed().update[0].time, test4->get_processed().update[1].time);

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

	ie::Animator animator{{test1, test2}};

	delete animator.copy();

	ASSERT_EQ(test1->get_processed().copy.size(), 1);
	ASSERT_EQ(test2->get_processed().copy.size(), 1);
	ASSERT_EQ(test1_1->get_processed().copy.size(), 1);
	ASSERT_EQ(test1_2->get_processed().copy.size(), 1);
	ASSERT_EQ(test2_1->get_processed().copy.size(), 1);
	ASSERT_EQ(test2_2->get_processed().copy.size(), 1);

	animator.update(3.f);
	delete animator.copy();

	ASSERT_EQ(test1->get_processed().copy.size(), 2);
	ASSERT_EQ(test2->get_processed().copy.size(), 2);
	ASSERT_EQ(test1_1->get_processed().copy.size(), 2);
	ASSERT_EQ(test1_2->get_processed().copy.size(), 2);
	ASSERT_EQ(test2_1->get_processed().copy.size(), 2);
	ASSERT_EQ(test2_2->get_processed().copy.size(), 2);

	delete test1_1;
	delete test1_2;
	delete test2_1;
	delete test2_2;
}