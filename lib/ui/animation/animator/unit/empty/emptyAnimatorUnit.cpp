#include "emptyAnimatorUnit.hpp"

namespace ui {
	void EmptyAnimatorUnit::restart() {}

	IAnimatorUnit *EmptyAnimatorUnit::update(float time) {
		return this;
	}
} // ui