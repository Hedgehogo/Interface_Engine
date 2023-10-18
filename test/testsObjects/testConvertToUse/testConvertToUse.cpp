#include "test_convert_to_use.hpp"

#include "../processor_time.hpp"

TestConvertToUse::TestConvertToUse(float result) : result(result) {}

const TestConvertToUse::Processed &TestConvertToUse::get_processed() const {
	return processed;
}

float TestConvertToUse::convert(float value) {
	processed.convert.push_back({get_processor_time(), value});
	return result;
}
