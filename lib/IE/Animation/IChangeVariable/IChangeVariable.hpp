#pragma once

#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class IChangeVariable {
	public:
		virtual float getSize() = 0;
		
		virtual float operator()(float frame) = 0;
		
		virtual IChangeVariable* copy() = 0;
		
		virtual ~IChangeVariable() = default;
	};
}