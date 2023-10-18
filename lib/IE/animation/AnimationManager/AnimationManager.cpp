#include "AnimationManager.hpp"

namespace ie {
	uint64_t get_time() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
	
	AnimationManager::AnimationManager(std::vector<Animator*> animators) : animators(animators) {
		start_manager = get_time();
	}
	
	void AnimationManager::update() {
		float current_time = static_cast<double>(get_time() - start_manager) / 1000;
		for(auto& animator: animators) {
			animator->update(current_time);
		}
	}
	
	AnimationManager* AnimationManager::copy() {
		std::vector<Animator*> result;
		
		for(auto& item: animators) {
			result.push_back(item->copy());
		}
		
		return new AnimationManager{result};
	}
	
	AnimationManager::~AnimationManager() {
		std::destroy(animators.begin(), animators.end());
	}
	
	bool Decode<AnimationManager>::decode(const YAML::Node& node, AnimationManager& animation_manager) {
		animation_manager = AnimationManager{
			node["animator"] ? std::vector<Animator*>{node["animator"].as<Animator*>()} : node["animators"].as<std::vector<Animator*> >()
		};
		
		animator_unit_request_update();
		
		return true;
	}
}