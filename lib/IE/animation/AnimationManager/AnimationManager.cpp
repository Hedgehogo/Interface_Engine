#include "AnimationManager.hpp"

namespace ie {
	uint64_t get_time() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
	
	AnimationManager::AnimationManager(std::vector<Animator*> animators) : animators_(animators) {
		start_time_ = get_time();
	}
	
	void AnimationManager::update() {
		float current_time = static_cast<double>(get_time() - start_time_) / 1000;
		for(auto& animator: animators_) {
			animator->update(current_time);
		}
	}
	
	AnimationManager* AnimationManager::copy() {
		std::vector<Animator*> result;
		
		for(auto& item: animators_) {
			result.push_back(item->copy());
		}
		
		return new AnimationManager{result};
	}
	
	AnimationManager::~AnimationManager() {
		std::destroy(animators_.begin(), animators_.end());
	}
	
	/*old_yaml_decode_impl
	bool Decode<AnimationManager>::decode(const YAML::Node& node, AnimationManager& animation_manager) {
		animation_manager = AnimationManager{
			node["animator"] ? std::vector<Animator*>{node["animator"].as<Animator*>()} : node["animators"].as<std::vector<Animator*> >()
		};
		
		animator_unit_request_update();
		
		return true;

	}
	*/
}