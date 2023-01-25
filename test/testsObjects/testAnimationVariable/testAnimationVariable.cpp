#include "testAnimationVariable.hpp"
#include "../processorTime.hpp"

TestAnimationVariable::TestAnimationVariable() {}

void TestAnimationVariable::valueFromAnimation(float newValue) {
	processed.valueFromAnimation.push_back({getProcessorTime(), newValue});
}

TestAnimationVariable::Processed TestAnimationVariable::getProcessed() const {
	return processed;
}