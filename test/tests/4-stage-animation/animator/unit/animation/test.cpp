#include <gtest/gtest.h>
#include "IE/Animation/Animator/IAnimatorUnit/Animation/Animation.hpp"
#include "../test/tests_objects/test_animation_variable/test_animation_variable.hpp"
#include "../test/tests_objects/test_change_variable/test_change_variable.hpp"
#include "../test/tests_objects/test_animator_unit/test_animator_unit.hpp"

TEST(Animation, update) {
	auto *test_change_variable1a = new TestChangeVariable{1, 2},
					   *test_change_variable1b = new TestChangeVariable{1, 2},
					   *test_change_variable2a = new TestChangeVariable{1, 2},
					   *test_change_variable2b = new TestChangeVariable{1, 2};
	auto *test_animation_variable1 = new TestAnimationVariable{},
						  *test_animation_variable2 = new TestAnimationVariable{};
	auto *test_animator_unit = new TestAnimatorUnit{};
	ie::Animation animation{
		{
			{
				test_animation_variable1,
				{test_change_variable1a, test_change_variable1b}
			},
			{
				test_animation_variable2,
				{test_change_variable2a, test_change_variable2b}
			}
		},
		{test_animator_unit, nullptr}
	};

	auto next_anim = animation.update(0.1);

	ASSERT_EQ(next_anim.size(), 1);
	ASSERT_EQ(next_anim[0], &animation);

	ASSERT_EQ(test_change_variable1a->get_processed().operat[0].frame, 0);
	ASSERT_EQ(test_change_variable2a->get_processed().operat[0].frame, 0);

	ASSERT_EQ(test_change_variable1b->get_processed().operat.size(), 0);
	ASSERT_EQ(test_change_variable2b->get_processed().operat.size(), 0);

	next_anim = animation.update(0.5);

	ASSERT_EQ(next_anim.size(), 1);
	ASSERT_EQ(next_anim[0], &animation);

	ASSERT_EQ(test_change_variable1a->get_processed().operat[1].frame, 0.4f);
	ASSERT_EQ(test_change_variable2a->get_processed().operat[1].frame, 0.4f);

	ASSERT_EQ(test_change_variable1b->get_processed().operat.size(), 0);
	ASSERT_EQ(test_change_variable2b->get_processed().operat.size(), 0);

	next_anim = animation.update(1.5);

	ASSERT_EQ(next_anim.size(), 1);
	ASSERT_EQ(next_anim[0], &animation);

	ASSERT_EQ(test_change_variable1a->get_processed().operat.size(), 2);
	ASSERT_EQ(test_change_variable2a->get_processed().operat.size(), 2);


	ASSERT_EQ(test_change_variable1b->get_processed().operat[0].frame, 1.4f);
	ASSERT_EQ(test_change_variable2b->get_processed().operat[0].frame, 1.4f);

	next_anim = animation.update(3);

	ASSERT_EQ(next_anim.size(), 2);
	ASSERT_EQ(next_anim[0], test_animator_unit);
	ASSERT_EQ(next_anim[1], &animation);
}

TEST(Animation, restart) {
	auto *test_change_variable = new TestChangeVariable{1, 2};
	auto *test_animation_variable = new TestAnimationVariable{};
	ie::Animation animation{
		{
			{
				test_animation_variable,
				{
					test_change_variable
				}
			}
		}
	};

	animation.update(0.1);

	ASSERT_EQ(test_change_variable->get_processed().operat[0].frame, 0);

	animation.update(1.1);

	ASSERT_EQ(test_change_variable->get_processed().operat[1].frame, 1);

	animation.restart();
	animation.update(0.1);

	ASSERT_EQ(test_change_variable->get_processed().operat[2].frame, 0);
}

TEST(Animation, set_next_units) {
	auto *test_change_variable = new TestChangeVariable{1, 2};
	auto *test_animation_variable = new TestAnimationVariable{};
	auto *test_animator_unit1 = new TestAnimatorUnit{},
					 *test_animator_unit2 = new TestAnimatorUnit{},
					 *test_animator_unit3 = new TestAnimatorUnit{};
	ie::Animation animation{
		{
			{
				test_animation_variable,
				{
					test_change_variable
				}
			}
		},
		{test_animator_unit1}
	};

	animation.update(0.1);
	auto next = animation.update(2);
	ASSERT_EQ(next.size(), 1);
	ASSERT_EQ(next[0], test_animator_unit1);
	animation.restart();

	animation.set_next_units({test_animator_unit2, test_animator_unit3});
	animation.update(0.1);
	next = animation.update(2);
	ASSERT_EQ(next.size(), 2);
	ASSERT_EQ(next[0], test_animator_unit2);
	ASSERT_EQ(next[1], test_animator_unit3);

	delete test_animator_unit2;
	delete test_animator_unit3;
}

TEST(Animation, add_next_units) {
	auto *test_change_variable = new TestChangeVariable{1, 2};
	auto *test_animation_variable = new TestAnimationVariable{};
	auto *test_animator_unit1 = new TestAnimatorUnit{},
					 *test_animator_unit2 = new TestAnimatorUnit{};
	ie::Animation animation{
		{
			{
				test_animation_variable,
				{
					test_change_variable
				}
			}
		},
		{test_animator_unit1}
	};

	animation.update(0.1);
	auto next = animation.update(2);
	ASSERT_EQ(next.size(), 1);
	ASSERT_EQ(next[0], test_animator_unit1);
	animation.restart();

	animation.add_next_units(test_animator_unit2);
	animation.update(0.1);
	next = animation.update(2);
	ASSERT_EQ(next.size(), 2);
	ASSERT_EQ(next[0], test_animator_unit1);
	ASSERT_EQ(next[1], test_animator_unit2);

	delete test_animator_unit2;
}

TEST(Animation, copy) {
	auto *test_change_variable = new TestChangeVariable{1, 2};
	auto *test_animation_variable = new TestAnimationVariable{};
	auto *test_animator_unit1 = new TestAnimatorUnit{},
		 *test_animator_unit2 = new TestAnimatorUnit{},
		 *test_animator_unit3 = new TestAnimatorUnit{},
		 *test_animator_unit4 = new TestAnimatorUnit{},
		 *test_animator_unit5 = new TestAnimatorUnit{};
	ie::Animation animation1{
		{
			{
				test_animation_variable,
				{
					test_change_variable
				}
			}
		},
		{test_animator_unit1}
	};
	animation1.set_next_units({test_animator_unit2, test_animator_unit3});

	delete animation1.copy();

	ASSERT_EQ(test_change_variable->get_processed().copy.size(), 1);
	ASSERT_EQ(test_animator_unit1->get_processed().copy.size(), 1);
	ASSERT_EQ(test_animator_unit2->get_processed().copy.size(), 0);
	ASSERT_EQ(test_animator_unit3->get_processed().copy.size(), 0);

	ie::Animation animation2{
		{
			{
				test_animation_variable,
				{
					test_change_variable
				}
			}
		},
		{test_animator_unit4}
	};
	animation2.add_next_units(test_animator_unit5);

	delete animation2.copy();

	ASSERT_EQ(test_animator_unit4->get_processed().copy.size(), 1);
	ASSERT_EQ(test_animator_unit5->get_processed().copy.size(), 0);

	delete test_animator_unit2;
	delete test_animator_unit3;
	delete test_animator_unit5;
}
