#pragma once

#include <chrono>
#include <vector>
#include "../Animator/Animator.hpp"

namespace ie {
	class AnimationManager {
	public:
		explicit AnimationManager(std::vector<Animator*> animators = {});
		
		virtual void update();
		
		virtual AnimationManager* copy();
		
		virtual ~AnimationManager();
	
	protected:
		uint64_t startManager;
		std::vector<Animator*> animators;
	};
	
	template<>
	struct Decode<AnimationManager> {
		static bool decode(const YAML::Node& node, AnimationManager& animationManager);
	};
}