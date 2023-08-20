#include <gtest/gtest.h>
#include "IE/Animation/AnimationManager/AnimationManager.hpp"
#include "../../../testsObjects/testAnimatorUnit/testAnimatorUnit.hpp"

TEST(AnimationManager, update) {
	TestAnimatorUnit *test1 = new TestAnimatorUnit{}, *test2 = new TestAnimatorUnit{};

	ui::AnimationManager animationManager{
		{
			new ui::Animator{
				{
					test1
				}
			},
			new ui::Animator{
				{
				    test2
			    }
			},
		}
	};

	animationManager.update();

	ASSERT_LT(test1->getProcessed().update[0].time, test2->getProcessed().update[0].time);
	ASSERT_EQ(test1->getProcessed().update[0].timeParameter, test2->getProcessed().update[0].timeParameter);
}

TEST(AnimationManager, copy) {
	TestAnimatorUnit *test1 = new TestAnimatorUnit{}, *test2 = new TestAnimatorUnit{};

	ui::AnimationManager animationManager{
		{
			new ui::Animator{
				{
					test1
				}
			},
			new ui::Animator{
				{
					test2
				}
			},
		}
	};

	animationManager.copy();

	ASSERT_NE(test1->getProcessed().copy[0], 0);
	ASSERT_LT(test1->getProcessed().copy[0], test2->getProcessed().copy[0]);
}