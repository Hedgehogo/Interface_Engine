#include "testAnimatorUnit.hpp"
#include "../processorTime.hpp"

TestAnimatorUnit::TestAnimatorUnit(std::vector<IAnimatorUnit *> updateResult) : updateResult(updateResult) {}

TestAnimatorUnit::Processed TestAnimatorUnit::getProcessed() {
	return processed;
}

void TestAnimatorUnit::restart() {
	processed.restart.push_back(getProcessorTime());
}

std::vector<ui::IAnimatorUnit *> TestAnimatorUnit::update(float time) {
	processed.update.push_back({getProcessorTime(), time});
	return updateResult;
}

void TestAnimatorUnit::setNextUnits(std::vector<IAnimatorUnit *> nextUnits) {
	processed.setNextUnits.push_back({getProcessorTime(), nextUnits});
}

void TestAnimatorUnit::addNextUnits(ui::IAnimatorUnit *nextUnit) {
	processed.addNextUnits.push_back({getProcessorTime(), nextUnit});
}

TestAnimatorUnit *TestAnimatorUnit::copy() {
	processed.copy.push_back(getProcessorTime());

	std::vector<IAnimatorUnit *> copyUpdateResult{updateResult.size()};

	for (size_t i = 0; i < copyUpdateResult.size(); ++i) {
		copyUpdateResult[i] = updateResult[i]->copy();
	}
	
	return new TestAnimatorUnit{copyUpdateResult};
}
