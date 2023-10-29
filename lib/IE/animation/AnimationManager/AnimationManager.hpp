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
		uint64_t start_time_;
		std::vector<Animator*> animators_;
	};
	
	/*old_yaml_decode
	template<>
	struct Decode<AnimationManager> {
		static bool decode(const YAML::Node& node, AnimationManager& animation_manager);
	};
	*/
}