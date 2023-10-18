#include "test_animator_unit.hpp"
#include "../processor_time.hpp"

TestAnimatorUnit::TestAnimatorUnit(std::vector<IAnimatorUnit *> update_result) : update_result(update_result) {
	for (size_t i = 0; i < update_result.size(); ++i) {
		if (!this->update_result[i]) this->update_result[i] = this;
	}
}

TestAnimatorUnit::Processed TestAnimatorUnit::get_processed() {
	return processed;
}

void TestAnimatorUnit::restart() {
	processed.restart.push_back(get_processor_time());
}

std::vector<ie::IAnimatorUnit *> TestAnimatorUnit::update(float time) {
	processed.update.push_back({get_processor_time(), time});
	return update_result;
}

void TestAnimatorUnit::set_next_units(std::vector<IAnimatorUnit *> next_units) {
	processed.set_next_units.push_back({get_processor_time(), next_units});
}

void TestAnimatorUnit::add_next_units(ie::IAnimatorUnit *next_unit) {
	processed.add_next_units.push_back({get_processor_time(), next_unit});
}

TestAnimatorUnit *TestAnimatorUnit::copy() {
	processed.copy.push_back(get_processor_time());

	std::vector<IAnimatorUnit *> copy_update_result{update_result.size()};

	for (size_t i = 0; i < copy_update_result.size(); ++i) {
		copy_update_result[i] = update_result[i]->copy();
	}
	
	return new TestAnimatorUnit{copy_update_result};
}
