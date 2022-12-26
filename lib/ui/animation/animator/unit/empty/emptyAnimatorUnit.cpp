#include "emptyAnimatorUnit.hpp"

namespace ui {
	void EmptyAnimatorUnit::restart() {}

	IAnimatorUnit *EmptyAnimatorUnit::update(float time) {
		return this;
	}

	void EmptyAnimatorUnit::setNextUnit(IAnimatorUnit *nextUnit) {}
} // ui