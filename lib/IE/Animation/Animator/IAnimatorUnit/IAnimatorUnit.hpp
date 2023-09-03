#pragma once

#include "IE/Modules/yaml-animation/buffer.hpp"
#include "IE/Modules/yaml-cpp/shared/value/general/sValue.hpp"

namespace ie {
	class IAnimatorUnit {
	public:
		virtual void setSpeed(PSfloat speed) = 0;
		
		virtual void restart() = 0;
		
		virtual std::vector<IAnimatorUnit*> update(float time) = 0;
		
		virtual IAnimatorUnit* copy() = 0;
		
		virtual ~IAnimatorUnit() = default;
	};
	
	std::vector<IAnimatorUnit*> getAnimatorUnits(const YAML::Node& node, std::string nameNextNode = "next");
}