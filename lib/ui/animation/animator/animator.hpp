#pragma once

#include "unit/iAnimatorUnit.hpp"

namespace ui {
	class Animator {
	protected:
		IAnimatorUnit* unit;

	public:
		explicit Animator(IAnimatorUnit *unit);

		void update(float time);

		virtual Animator* copy();

		~Animator();
	};

	bool convertPointer(const YAML::Node &node, Animator*& animator);
} // ui