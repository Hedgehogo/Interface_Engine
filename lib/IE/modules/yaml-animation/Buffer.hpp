#pragma once

#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"
#include <functional>

namespace ie {
	class AnimationManager;
	
	class IAnimatorUnit;
	
	extern std::map<std::string, std::vector<std::function<void(IAnimatorUnit*)>>> animatorUnitRequest;
	extern std::map<std::string, IAnimatorUnit*> animatorUnitBuffer;
	
	void animatorUnitRequestUpdate();
	
	void addNextAnimatorUnit(const YAML::Node& node, std::function<void(IAnimatorUnit*)> fun, std::string nameNextNode = "next");
	
	void addUnitInBuffer(const YAML::Node& node, IAnimatorUnit* unit, std::string name = "name");
}
