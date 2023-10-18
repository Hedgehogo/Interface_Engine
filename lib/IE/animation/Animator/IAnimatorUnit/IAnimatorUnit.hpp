#pragma once

#include "IE/modules/yaml-animation/Buffer.hpp"
#include "IE/modules/yaml-cpp/shared/ISValue/SValue/SValue.hpp"

namespace ie {
	class IAnimatorUnit {
	public:
		virtual void set_speed(PSfloat speed) = 0;
		
		virtual void restart() = 0;
		
		virtual std::vector<IAnimatorUnit*> update(float time) = 0;
		
		virtual IAnimatorUnit* copy() = 0;
		
		virtual ~IAnimatorUnit() = default;
	};
	
	std::vector<IAnimatorUnit*> get_animator_units(const YAML::Node& node, std::string name_next_node = "next");
}