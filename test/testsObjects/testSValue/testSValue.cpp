#include "testSValue.hpp"

#include "../processorTime.hpp"

TestSValue::TestSValue(float resultGet) : resultGet(resultGet) {}

const TestSValue::Processed &TestSValue::getProcessed() const {
	return processed;
}

void TestSValue::addSetter(const TestSValue::ISValue::SetterFunc &setter) {
	processed.addSetter.push_back({getProcessorTime(), setter});
}

const float &TestSValue::getValue() const {
	return resultGet;
}

void TestSValue::setValue(const float &value) {
	processed.setValue.push_back({getProcessorTime(), value});
}
