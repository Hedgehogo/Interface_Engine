#include "AnimationManager.hpp"

namespace ui {
	uint64_t getTime() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
	
	AnimationManager::AnimationManager(std::vector<Animator*> animators) : animators(animators) {
		startManager = getTime();
	}
	
	void AnimationManager::update() {
		float currentTime = static_cast<double>(getTime() - startManager) / 1000;
		for(auto& animator: animators) {
			animator->update(currentTime);
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
	
	bool Decode<AnimationManager>::decode(const YAML::Node& node, AnimationManager& animationManager) {
		animationManager = AnimationManager{
			node["animator"] ? std::vector<Animator*>{node["animator"].as<Animator*>()} : node["animators"].as<std::vector<Animator*> >()
		};
		
		animatorUnitRequestUpdate();
		
		return true;
	}
}