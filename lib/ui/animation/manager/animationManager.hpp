#pragma once

#include <chrono>
#include <vector>
#include "../animator/animator.hpp"

namespace ui {
	class AnimationManager {
	protected:
		uint64_t startManager;
		std::vector<Animator*> animators;

	public:
		explicit AnimationManager(std::vector<Animator*> animators = {});

		virtual void update();

		virtual AnimationManager* copy();

		virtual ~AnimationManager();
	};

	template<>
	bool convert(const YAML::Node &node, AnimationManager& animationManager);
}