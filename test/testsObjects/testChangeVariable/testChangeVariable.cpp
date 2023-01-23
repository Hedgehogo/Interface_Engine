#include "testChangeVariable.hpp"

#include "../processorTime.hpp"

TestChangeVariable::TestChangeVariable(float size, float result) : size(size), result(result) {}

const TestChangeVariable::Processed &TestChangeVariable::getProcessed() const {
	return processed;
}

float TestChangeVariable::getSize() {
	processed.getSize.push_back(getProcessorTime());
	return size;
}

float TestChangeVariable::operator()(float frame) {
	processed.operat.push_back({getProcessorTime(), frame});
	return result;
}

ui::IChangeVariable *TestChangeVariable::copy() {
	processed.copy.push_back(getProcessorTime());
	return new TestChangeVariable{size, result};
}
