#include "test_animation_variable.hpp"
#include "../processor_time.hpp"

TestAnimationVariable::TestAnimationVariable() {}

void TestAnimationVariable::value_from_animation(float new_value) {
	processed.value_from_animation.push_back({get_processor_time(), new_value});
}

TestAnimationVariable::Processed TestAnimationVariable::get_processed() const {
	return processed;
}
