#pragma once

#include "unit/iAnimatorUnit.hpp"

namespace ui {
	class Animator {
	protected:
		std::vector<IAnimatorUnit*> units;
		std::vector<IAnimatorUnit*> unitsBuff;
		float speed;

	public:
		explicit Animator(std::vector<IAnimatorUnit *> units, float speed);

		void update(float time);

		virtual Animator* copy();

		~Animator();
	};

	bool convertPointer(const YAML::Node &node, Animator*& animator);
} // ui