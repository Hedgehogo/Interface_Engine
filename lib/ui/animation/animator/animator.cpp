#include "animator.hpp"

namespace ui {
	Animator::Animator(IAnimatorUnit *unit) : unit(unit) {}

	void Animator::update(float time) {
		unit = unit->update(time);
	}

	Animator *Animator::copy() {
		return new Animator{unit};
	}

	Animator::~Animator() {
		delete unit;
	}
} // ui