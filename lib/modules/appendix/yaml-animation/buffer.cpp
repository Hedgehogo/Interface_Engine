#include "../../../ui/animation/animator/unit/iAnimatorUnit.hpp"
#include "buffer.hpp"

namespace ui{

	std::map<std::string, IAnimationVariable*> animationVariablesBuffer;
	std::map<std::string, std::vector<std::function<void(IAnimatorUnit*)>>> animatorUnitRequest;
	std::map<std::string, IAnimatorUnit*> animatorUnitBuffer;

	void animatorUnitRequestUpdate(){
		for (auto& requesters : animatorUnitRequest) {
			for (auto& requester : requesters.second){
				requester(animatorUnitBuffer[requesters.first]);
			}
		}
	}
}
