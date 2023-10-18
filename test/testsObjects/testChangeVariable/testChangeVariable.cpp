#include "test_change_variable.hpp"

#include "../processor_time.hpp"

TestChangeVariable::TestChangeVariable(float size, float result) : size(size), result(result) {}

const TestChangeVariable::Processed &TestChangeVariable::get_processed() const {
	return processed;
}

float TestChangeVariable::get_size() {
	processed.get_size.push_back(get_processor_time());
	return size;
}

float TestChangeVariable::operator()(float frame) {
	processed.operat.push_back({get_processor_time(), frame});
	return result;
}

ie::IChangeVariable *TestChangeVariable::copy() {
	processed.copy.push_back(get_processor_time());
	return new TestChangeVariable{size, result};
}
