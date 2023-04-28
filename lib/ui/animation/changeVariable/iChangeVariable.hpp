#pragma once

#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class IChangeVariable {
	public:
		virtual float getSize() = 0;
		
		virtual float operator()(float frame) = 0;
		
		virtual IChangeVariable* copy() = 0;
	};
}