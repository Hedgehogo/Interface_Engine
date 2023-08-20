#include <gtest/gtest.h>
#include "IE/animation/convertToUse/coefficientWithRange/convertToUseCoefficientWithRange.hpp"

TEST(ConvertToUseCoefficientWithRange, operatop){
	ui::ConvertToUseCoefficientWithRange<float> coefficientWithRange1{0, 20, 3},
		coefficientWithRange2{0.5, 20, 3},
		coefficientWithRange3{1, 20, 3},
		coefficientWithRange4{11, 20, 3};

	ASSERT_EQ(coefficientWithRange1(7), 3);
	ASSERT_EQ(coefficientWithRange2(7), 3.5);
	ASSERT_EQ(coefficientWithRange3(7), 7);
	ASSERT_EQ(coefficientWithRange4(7), 20);
}
