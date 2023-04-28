#pragma once

#include "../yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include <functional>

namespace ui{

	class AnimationManager;
	class IAnimatorUnit;

	extern std::map<std::string, std::vector<std::function<void(IAnimatorUnit*)>>> animatorUnitRequest;
	extern std::map<std::string, IAnimatorUnit*> animatorUnitBuffer;

	void animatorUnitRequestUpdate();
	
	void addNextAnimatorUnit(const YAML::Node& node, std::function<void(IAnimatorUnit*)> fun, std::string nameNextNode = "next");
	
	void addUnitInBuffer(const YAML::Node& node, IAnimatorUnit* unit, std::string name = "name");
}
