#include "emptyAnimatorUnit.hpp"

namespace ui {
	void EmptyAnimatorUnit::restart() {}

	std::vector<IAnimatorUnit*> EmptyAnimatorUnit::update(float time) {
		return {this};
	}

	void EmptyAnimatorUnit::setNextUnits(std::vector<IAnimatorUnit*> nextUnits) {}

	void EmptyAnimatorUnit::addNextUnits(IAnimatorUnit *nextUnit) {}
} // ui