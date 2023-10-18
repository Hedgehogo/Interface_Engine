#include <gtest/gtest.h>
#include "IE/Animation/AnimationManager/AnimationManager.hpp"
#include "../../../tests_objects/test_animator_unit/test_animator_unit.hpp"

TEST(AnimationManager, update) {
	TestAnimatorUnit *test1 = new TestAnimatorUnit{}, *test2 = new TestAnimatorUnit{};

	ie::AnimationManager animation_manager{
		{
			new ie::Animator{
				{
					test1
				}
			},
			new ie::Animator{
				{
				    test2
			    }
			},
		}
	};

	animation_manager.update();

	ASSERT_LT(test1->get_processed().update[0].time, test2->get_processed().update[0].time);
	ASSERT_EQ(test1->get_processed().update[0].time_parameter, test2->get_processed().update[0].time_parameter);
}

TEST(AnimationManager, copy) {
	TestAnimatorUnit *test1 = new TestAnimatorUnit{}, *test2 = new TestAnimatorUnit{};

	ie::AnimationManager animation_manager{
		{
			new ie::Animator{
				{
					test1
				}
			},
			new ie::Animator{
				{
					test2
				}
			},
		}
	};

	animation_manager.copy();

	ASSERT_NE(test1->get_processed().copy[0], 0);
	ASSERT_LT(test1->get_processed().copy[0], test2->get_processed().copy[0]);
}