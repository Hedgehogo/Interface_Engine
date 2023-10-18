#include "test_s_value.hpp"

#include "../processor_time.hpp"

TestSValue::TestSValue(float result_get) : result_get(result_get) {}

const TestSValue::Processed &TestSValue::get_processed() const {
	return processed;
}

void TestSValue::add_setter(const TestSValue::ISValue::SetterFunc &setter) {
	processed.add_setter.push_back({get_processor_time(), setter});
}

const float &TestSValue::get_value() const {
	return result_get;
}

void TestSValue::set_value(const float &value) {
	processed.set_value.push_back({get_processor_time(), value});
}
