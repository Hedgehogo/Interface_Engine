#pragma once

#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class BaseChangeVariable {
	public:
		virtual float getSize() = 0;

		virtual float operator()(float frame) = 0;
	};
}