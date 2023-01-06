#include "testConvertToUse.hpp"

#include "../processorTime.hpp"

TestConvertToUse::TestConvertToUse(float result) : result(result) {}

const TestConvertToUse::Processed &TestConvertToUse::getProcessed() const {
	return processed;
}

float TestConvertToUse::convert(float value) {
	processed.convert.push_back({getProcessorTime(), value});
	return result;
}
