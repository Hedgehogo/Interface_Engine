#include <gtest/gtest.h>
#include "IE/Animation/convert_to_use/coefficient_with_range/convert_to_use_coefficient_with_range.hpp"

TEST(ConvertToUseCoefficientWithRange, operatop){
	ie::ConvertToUseCoefficientWithRange<float> coefficient_with_range1{0, 20, 3},
		coefficient_with_range2{0.5, 20, 3},
		coefficient_with_range3{1, 20, 3},
		coefficient_with_range4{11, 20, 3};

	ASSERT_EQ(coefficient_with_range1(7), 3);
	ASSERT_EQ(coefficient_with_range2(7), 3.5);
	ASSERT_EQ(coefficient_with_range3(7), 7);
	ASSERT_EQ(coefficient_with_range4(7), 20);
}
