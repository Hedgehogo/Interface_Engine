#pragma once

#include "unit/iAnimatorUnit.hpp"

namespace ui {
	class Animator {
	protected:
		std::vector<IAnimatorUnit*> units;
		std::vector<IAnimatorUnit*> unitsBuff;

	public:
		explicit Animator(std::vector<IAnimatorUnit*> units);

		void update(float time);

		virtual Animator* copy();

		~Animator();
	};

	bool convertPointer(const YAML::Node &node, Animator*& animator);
} // ui